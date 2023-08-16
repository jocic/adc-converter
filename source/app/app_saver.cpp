#include <QDebug>
#include <QMutexLocker>
#include <QProgressBar>
#include <QMessageBox>
#include <QStringList>
#include <QFile>

#include "app/mvc/element_manager.h"
#include "popovers/processing/processing_model.h"
#include "app/workers/save_worker.h"
#include "app/app_saver.h"

AppSaver* AppSaver::M_INSTANCE = NULL;
QMutex     AppSaver::M_MUTEX;

AppSaver* AppSaver::get_Instance() {
    
    QMutexLocker locker(&M_MUTEX);
    
    if (M_INSTANCE == NULL) {
        M_INSTANCE = new AppSaver();
    }
    
    return M_INSTANCE;
}

AppSaver::AppSaver() {
    
    // Initialize Core Member Variables
    
    QByteArray*        buffer  = new QByteArray();
    ProcessingPopover* popover = new ProcessingPopover();
    SaveWorker*        worker  = new SaveWorker();
    
    popover->initialize();
    
    ElementManager* popover_manager = popover
        ->view()->get_ElementManager();
    
    QProgressBar* progress_bar = (QProgressBar*)popover_manager
        ->get(ProcessingModel::FIELD_PROGRESS);
    
    progress_bar->setValue(0);
    
    // Setup Dialog
    
    QString dump_filename = "dump_" +
        QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".dat";
    
    this->setWindowTitle("Save Dump");
    this->setAcceptMode(QFileDialog::AcceptSave);
    this->setLabelText(QFileDialog::DialogLabel::Accept, "Save");
    this->selectFile(dump_filename);
    
    // Connect Everything
    
    connect(worker, &SaveWorker::sig_Error,
        this, &AppSaver::on_Error);
    
    connect(worker, &SaveWorker::sig_Done,
        this, &AppSaver::on_Done);
    
    connect(worker, &SaveWorker::sig_Progressed,
        progress_bar, &QProgressBar::setValue);
    
    connect(popover, &ProcessingPopover::sig_Abort,
        this, &AppSaver::on_Abort);
    
    connect(popover, &ProcessingPopover::finished,
        this, &AppSaver::on_Abort);
    
    // Set References
    
    this->set_Buffer(buffer);
    this->set_Popover(popover);
    this->set_Worker(worker);
}

void AppSaver::process(QByteArray* buffer) {
    
    if (!this->is_Selected()) {
        return;
    }
    
    QString filename = this->selectedFiles().front();
    QFile*  file     = new QFile(filename);
    
    qDebug() << "Processing:" << filename;
    
    this->get_Buffer()->clear();
    
    this->get_Worker()->set_File(file);
    this->get_Worker()->set_Buffer(buffer);
    this->get_Worker()->start();
    
    this->get_Popover()->setVisible(true);
}



