#include <QDebug>
#include <QMutexLocker>
#include <QProgressBar>
#include <QMessageBox>
#include <QStringList>
#include <QFile>

#include "app/mvc/element_manager.h"
#include "popovers/processing/processing_model.h"
#include "app/workers/export_worker.h"
#include "app/app_exporter.h"

AppExporter* AppExporter::M_INSTANCE = NULL;
QMutex       AppExporter::M_MUTEX;

AppExporter* AppExporter::get_Instance() {
    
    QMutexLocker locker(&M_MUTEX);
    
    if (M_INSTANCE == NULL) {
        M_INSTANCE = new AppExporter();
    }
    
    return M_INSTANCE;
}

AppExporter::AppExporter() {
    
    // Initialize Core Member Variables
    
    QByteArray*        buffer  = new QByteArray();
    ProcessingPopover* popover = new ProcessingPopover();
    ExportWorker*      worker  = new ExportWorker();
    
    popover->initialize();
    
    ElementManager* popover_manager = popover
        ->view()->get_ElementManager();
    
    QProgressBar* progress_bar = (QProgressBar*)popover_manager
        ->get(ProcessingModel::FIELD_PROGRESS);
    
    progress_bar->setValue(0);
    
    // Setup Dialog
    
    QString export_filename = "export_" +
        QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".wav";
    
    this->setWindowTitle("Export Dump");
    this->setAcceptMode(QFileDialog::AcceptSave);
    this->setLabelText(QFileDialog::DialogLabel::Accept, "Export");
    this->selectFile(export_filename);
    
    // Connect Everything
    
    connect(worker, &ExportWorker::sig_Error,
        this, &AppExporter::on_Error);
    
    connect(worker, &ExportWorker::sig_Done,
        this, &AppExporter::on_Done);
    
    connect(worker, &ExportWorker::sig_Progressed,
        progress_bar, &QProgressBar::setValue);
    
    connect(popover, &ProcessingPopover::sig_Abort,
        this, &AppExporter::on_Abort);
    
    connect(popover, &ProcessingPopover::finished,
        this, &AppExporter::on_Abort);
    
    // Set References
    
    this->set_Buffer(buffer);
    this->set_Popover(popover);
    this->set_Worker(worker);
}

void AppExporter::process(QByteArray* buffer, quint64 sample_rate,
    quint8 bits_per_sample, bool signed_samples) {
    
    if (!this->is_Selected()) {
        return;
    }
    
    QString filename = this->selectedFiles().front();
    QFile*  file     = new QFile(filename);
    
    qDebug() << "Processing:" << filename
        << "Sample Rate:" << sample_rate
        << "Bits per Sample:" << bits_per_sample
        << "Signed Samples:" << signed_samples;
    
    this->get_Buffer()->clear();
    
    ExportWorker* worker = (ExportWorker*)this->get_Worker();
    
    worker->set_File(file);
    worker->set_Buffer(buffer);
    worker->set_SampleRate(sample_rate);
    worker->set_BitsPerSamplee(bits_per_sample);
    worker->set_SignedSamples(signed_samples);
    worker->start();
    
    this->get_Popover()->setVisible(true);
}



