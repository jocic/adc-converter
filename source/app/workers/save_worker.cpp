#include <QDebug>

#include "save_worker.h"

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
    
    quint64 chunk_size = this->calc_ChunkSize(m_Buffer->size());
    
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

