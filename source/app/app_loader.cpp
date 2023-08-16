#include <QDebug>
#include <QMutexLocker>
#include <QProgressBar>
#include <QMessageBox>
#include <QStringList>
#include <QFile>

#include "app/mvc/element_manager.h"
#include "popovers/processing/processing_model.h"
#include "app/workers/load_worker.h"
#include "app/app_loader.h"

AppLoader* AppLoader::M_INSTANCE = NULL;
QMutex      AppLoader::M_MUTEX;

AppLoader* AppLoader::get_Instance() {
    
    QMutexLocker locker(&M_MUTEX);
    
    if (M_INSTANCE == NULL) {
        M_INSTANCE = new AppLoader();
    }
    
    return M_INSTANCE;
}

AppLoader::AppLoader() {
    
    // Initialize Core Member Variables
    
    QByteArray*        buffer  = new QByteArray();
    ProcessingPopover* popover = new ProcessingPopover();
    LoadWorker*        worker  = new LoadWorker();   
    
    popover->initialize();
    
    ElementManager* popover_manager = popover
        ->view()->get_ElementManager();
    
    QProgressBar* progress_bar = (QProgressBar*)popover_manager
        ->get(ProcessingModel::FIELD_PROGRESS);
    
    progress_bar->setValue(0);
    
    // Setup Dialog
    
    this->setWindowTitle("Load Dump");
    this->setLabelText(QFileDialog::DialogLabel::Accept, "Load");
    
    // Connect Everything
    
    connect(worker, &LoadWorker::sig_Error,
        this, &AppLoader::on_Error);
    
    connect(worker, &LoadWorker::sig_Read,
        this, &AppLoader::on_Write);
    
    connect(worker, &LoadWorker::sig_Done,
        this, &AppLoader::on_Done);
    
    connect(worker, &LoadWorker::sig_Progressed,
        progress_bar, &QProgressBar::setValue);
    
    connect(popover, &ProcessingPopover::sig_Abort,
        this, &AppLoader::on_Abort);
    
    connect(popover, &ProcessingPopover::finished,
        this, &AppLoader::on_Abort);
    
    // Set References
    
    this->set_Buffer(buffer);
    this->set_Popover(popover);
    this->set_Worker(worker);
}

void AppLoader::process() {
    
    if (!this->is_Selected()) {
        return;
    }
    
    QString filename = this->selectedFiles().front();
    QFile*  file     = new QFile(filename);
    
    qDebug() << "Processing:" << filename;
    
    this->get_Buffer()->clear();
    
    this->get_Worker()->set_File(file);
    this->get_Worker()->start();
    
    this->get_Popover()->setVisible(true);
}



