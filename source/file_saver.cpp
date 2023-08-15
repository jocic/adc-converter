#include <QDebug>
#include <QMutexLocker>
#include <QProgressBar>
#include <QMessageBox>
#include <QStringList>
#include <QFile>

#include "app/mvc/element_manager.h"
#include "popovers/processing/processing_model.h"
#include "workers/save_worker.h"
#include "file_saver.h"

FileSaver* FileSaver::M_INSTANCE = NULL;
QMutex     FileSaver::M_MUTEX;

FileSaver* FileSaver::get_Instance() {
    
    QMutexLocker locker(&M_MUTEX);
    
    if (M_INSTANCE == NULL) {
        M_INSTANCE = new FileSaver();
    }
    
    return M_INSTANCE;
}

FileSaver::FileSaver() {
    
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
    
    this->setWindowTitle("Save Dump");
    this->setLabelText(QFileDialog::DialogLabel::Accept, "Save");
    
    // Connect Everything
    
    connect(worker, &SaveWorker::sig_Error,
        this, &FileSaver::on_Error);
    
    connect(worker, &SaveWorker::sig_Done,
        this, &FileSaver::on_Done);
    
    connect(worker, &SaveWorker::sig_Progressed,
        progress_bar, &QProgressBar::setValue);
    
    connect(popover, &ProcessingPopover::sig_Abort,
        this, &FileSaver::on_Abort);
    
    connect(popover, &ProcessingPopover::finished,
        this, &FileSaver::on_Abort);
    
    // Set References
    
    this->set_Buffer(buffer);
    this->set_Popover(popover);
    this->set_Worker(worker);
}

void FileSaver::process(QByteArray* buffer) {
    
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



