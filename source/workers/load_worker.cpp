#include "load_worker.h"

quint64 LoadWorker::get_OptimalChunkSize(QFile* file) {
    
    quint64 chunk_size = 1;
    
    if (file->size() < 10e6) {
        chunk_size = file->size() / 100;
    } else if (file->size() < 100e6) {
        chunk_size = file->size() / 1000;
    } else {
        chunk_size = file->size() / 10000;
    }
    
    chunk_size += (512 - (chunk_size % 512));
    
    qDebug() << "Calculated chunk size of " << chunk_size
        << " for " << file->size();
    
    return chunk_size;
}

void LoadWorker::start(QFile* file, Priority priority) {
    
    m_File = file;
    
    QThread::start();
}

void LoadWorker::run() {
    
    // Open File
    
    if (!m_File->isOpen() && !m_File->open(QFile::OpenModeFlag::ReadOnly)) {
        
        qDebug() << "File couldn't be open...";
        
        QFile::FileError error_code = m_File->error();
        
        emit LoadWorker::sig_Error(error_code);
    }
    
    // Read File
    
    quint64 chunk_size = this->get_OptimalChunkSize(m_File);
    
    while (!m_File->atEnd()) {
        
        QByteArray chunk = m_File->read(chunk_size);
        
        QFile::FileError error_code = m_File->error();
        
        if (error_code != QFile::FileError::NoError) {
            emit LoadWorker::sig_Error(error_code); break;
        }
        
        emit LoadWorker::sig_Chunk_Read(m_File, chunk);
        
        this->usleep(1000);
    }
    
    qDebug() << "File read completely...";
}
