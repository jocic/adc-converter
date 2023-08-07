#include <QDebug>
#include <QProgressBar>
#include <QMessageBox>
#include <QStringList>
#include <QFile>

#include "mvc/element_manager.h"
#include "popovers/processing/processing_model.h"
#include "file_loader.h"

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
    
    // Connect Everything
    
    connect(m_Worker, &LoadWorker::sig_Error,
        this, &FileLoader::on_Read_Error);
    
    connect(m_Worker, &LoadWorker::sig_Chunk_Read,
        this, &FileLoader::on_Chunk_Read);
    
    connect(this, &FileLoader::sig_Progress_Resize,
        progress_bar, &QProgressBar::setRange);
    
    connect(this, &FileLoader::sig_Progress_Update,
        progress_bar, &QProgressBar::setValue);
    
    connect(m_Popover, &ProcessingPopover::sig_Abort_Processing,
        this, &FileLoader::on_Abort_Processing);
}

QByteArray* FileLoader::buffer() {
    return m_Buffer;
}

void FileLoader::process() {
    
    QStringList files = this->selectedFiles();
    
    qDebug() << "Selected files:" << files.size();
    
    if (files.size() == 0) {
        return;
    }
    
    QFile* file = new QFile(files.front());
    
    m_Buffer->clear();
    
    m_Loaded = 0;
    
    m_Worker->start(file);
    m_Popover->setVisible(true);
    
    emit FileLoader::sig_Progress_Resize(0, 100);
}

void FileLoader::on_Read_Error(QFile::FileError error) {
    
    
}

void FileLoader::on_Chunk_Read(QFile* file, QByteArray chunk) {
    
    m_Loaded += chunk.size();
    
    quint8 progress = (double(m_Loaded) / file->size()) * 100;
    
    emit FileLoader::sig_Progress_Update(progress);
    
    if (m_Loaded == file->size()) {
        m_Popover->setVisible(false);
    }
    
    if (m_Buffer->size() <= 256e6) {
        *m_Buffer += chunk;
    } else {
        // abort processing
        // display an error to the user - your file was partially loaded
        // you can disable this limitation in options, bla bla
    }
}

void FileLoader::on_Abort_Processing() {
    
    qDebug() << "Handled abort signal...";
    
    m_Worker->terminate();
}
