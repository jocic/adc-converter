#include <QDebug>
#include <QByteArray>

#include "load_worker.h"

quint64 LoadWorker::get_OptimalChunkSize() {
    
    if (m_File == NULL) {
        qDebug() << "No file set...";
        return 0;
    }
    
    quint64 chunk_size = 1;
    
    if (m_File->size() < 10e6) {
        chunk_size = m_File->size() / 100;
    } else if (m_File->size() < 100e6) {
        chunk_size = m_File->size() / 1000;
    } else {
        chunk_size = m_File->size() / 10000;
    }
    
    chunk_size += (512 - (chunk_size % 512));
    
    qDebug() << "Calculated chunk size of " << chunk_size
        << " for " << m_File->size();
    
    return chunk_size;
}

void LoadWorker::run() {
    
    // Open File
    
    if (!m_File->isOpen() && !m_File->open(QFile::OpenModeFlag::ReadOnly)) {
        
        qDebug() << "File couldn't be open...";
        
        QFile::FileError error_code = m_File->error();
        
        emit LoadWorker::sig_Error(error_code);
    }
    
    quint64 read_bytes = 0;
    
    // Read File
    
    quint64 chunk_size = this->get_OptimalChunkSize();
    
    while (!m_File->atEnd()) {
        
        QByteArray chunk = m_File->read(chunk_size);
        
        QFile::FileError error_code = m_File->error();
        
        if (error_code != QFile::FileError::NoError) {
            emit LoadWorker::sig_Error(error_code); break;
        }
        
        read_bytes += chunk.size();
        
        quint8 progress = (double(read_bytes) / m_File->size()) * 100;
        
        emit LoadWorker::sig_Read(chunk);
        emit LoadWorker::sig_Progressed(progress);
        
        this->usleep(1000);
    }
    
    qDebug() << "File read completely...";
    
    emit LoadWorker::sig_Done();
}
