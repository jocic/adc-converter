#include <QDebug>

#include "save_worker.h"

quint64 SaveWorker::get_OptimalChunkSize() {
    
    if (m_Buffer == NULL) {
        qDebug() << "No buffer set...";
        return 0;
    }
    
    quint64 chunk_size = 1;
    
    if (m_Buffer->size() < 10e6) {
        chunk_size = m_Buffer->size() / 100;
    } else if (m_Buffer->size() < 100e6) {
        chunk_size = m_Buffer->size() / 1000;
    } else {
        chunk_size = m_Buffer->size() / 10000;
    }
    
    chunk_size += (512 - (chunk_size % 512));
    
    qDebug() << "Calculated chunk size of " << chunk_size
        << " for " << m_Buffer->size();
    
    return chunk_size;
}

void SaveWorker::run() {
    
    // Check Member Variables
    
    if (m_File == NULL || m_Buffer == NULL) {
        emit SaveWorker::sig_Done();
        return;
    }
    
    // Open File
    
    if (!m_File->isOpen() && !m_File->open(
        QFile::OpenModeFlag::WriteOnly | QFile::OpenModeFlag::Truncate)) {
        
        qDebug() << "File couldn't be open...";
        
        QFile::FileError error_code = m_File->error();
        
        emit SaveWorker::sig_Error(error_code);
        emit SaveWorker::sig_Done();
        
        return;
    }
    
    quint64 wrote_bytes = 0;
    
    // Read File
    
    quint64 chunk_size = this->get_OptimalChunkSize();
    
    for (quint64 i = 0; i < m_Buffer->size(); i+=chunk_size) {
        
        QByteArray chunk;
        
        quint64 max_slice = qMin(m_Buffer->size() - i, chunk_size);
        
        chunk += m_Buffer->sliced(i, max_slice);
        
        m_File->write(chunk);
        
        QFile::FileError error_code = m_File->error();
        
        if (error_code != QFile::FileError::NoError) {
            
            m_File->close();
            
            emit SaveWorker::sig_Error(error_code);
            emit SaveWorker::sig_Done();
            
            return;
        }
        
        wrote_bytes += chunk_size;
        
        quint8 progress = (double(wrote_bytes) / m_Buffer->size()) * 100;
        
        emit SaveWorker::sig_Wrote(chunk);
        emit SaveWorker::sig_Progressed(progress);
        
        this->usleep(1000);
    }
    
    qDebug() << "File written completely...";
    
    m_File->close();
    
    emit SaveWorker::sig_Done();
}

