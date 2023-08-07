#include <QDebug>
#include <QMutexLocker>
#include <QProgressBar>
#include <QMessageBox>
#include <QStringList>
#include <QFile>

#include "mvc/element_manager.h"
#include "popovers/processing/processing_model.h"
#include "file_loader.h"

FileLoader* FileLoader::M_INSTANCE = NULL;
QMutex      FileLoader::M_MUTEX;

FileLoader* FileLoader::get_Instance() {
    
    QMutexLocker locker(&M_MUTEX);
    
    if (M_INSTANCE == NULL) {
        M_INSTANCE = new FileLoader();
    }
    
    return M_INSTANCE;
}

FileLoader::FileLoader() {
    
    // Initialize Core Member Variables
    
    m_Buffer  = new QByteArray();
    m_Popover = new ProcessingPopover();
    m_Worker  = new LoadWorker();   
    
    m_Popover->initialize();
    
    ElementManager* popover_manager = m_Popover
        ->view()->get_ElementManager();
    
    QProgressBar* progress_bar = (QProgressBar*)popover_manager
        ->get(ProcessingModel::FIELD_PROGRESS);
    
    progress_bar->setValue(0);
    
    // Connect Everything
    
    connect(m_Worker, &LoadWorker::sig_Error,
        this, &FileLoader::on_Error);
    
    connect(m_Worker, &LoadWorker::sig_Read,
        this, &FileLoader::on_Read);
    
    connect(m_Worker, &LoadWorker::sig_Done,
        this, &FileLoader::on_Done);
    
    connect(m_Worker, &LoadWorker::sig_Progressed,
        progress_bar, &QProgressBar::setValue);
    
    connect(m_Popover, &ProcessingPopover::sig_Abort,
        this, &FileLoader::on_Abort);
    
    connect(m_Popover, &ProcessingPopover::finished,
        this, &FileLoader::on_Abort);
}

QByteArray* FileLoader::get_Buffer() {
    return m_Buffer;
}

QByteArray FileLoader::get_Chunk(quint64 off, quint64 len) {
    
    QByteArray chunk;
    
    if (off >= 0 && m_Buffer->size() >= (off + len)) {
        
        for (quint64 i = off, j = off + len; i < j; i++) {
            chunk.push_back(m_Buffer[i]);
        }
    }
    
    return chunk;
}

ProcessingPopover* FileLoader::get_Popover() {
    return m_Popover;
}

LoadWorker* FileLoader::get_Worker() {
    return m_Worker;
}

void FileLoader::process() {
    
    QStringList files = this->selectedFiles();
    
    qDebug() << "Selected files:" << files.size();
    
    if (files.size() == 0) {
        return;
    }
    
    QFile* file = new QFile(files.front());
    
    m_Buffer->clear();
    
    m_Worker->set_File(file);
    m_Worker->start();
    
    m_Popover->setVisible(true);
}

void FileLoader::clear() {
    m_Buffer->clear();
}

void FileLoader::on_Error(QFile::FileError error) {
    
    // Does nothing...
}

void FileLoader::on_Read(QByteArray chunk) {
    
    if (m_Buffer->size() <= 256e6) {
        
        *m_Buffer += chunk;
    }
    else {
        
        m_Worker->terminate();
        m_Popover->setVisible(false);
        
        QMessageBox alert;
        
        alert.setWindowTitle("I/O Warning");
        alert.setText("Files are read and temporarily stored in RAM. "
            "To prevent a crash, or a potential system failure, "
            "files over 256M in size are only partially loaded. "
            "You can disable this safety feature in options.");
        
        alert.exec();
    }
}

void FileLoader::on_Abort() {
    
    qDebug() << "Handled abort signal...";
    
    m_Worker->terminate();
}

void FileLoader::on_Done() {
    
    m_Popover->setVisible(false);
}
