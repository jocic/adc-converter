#include <QDebug>
#include <QByteArray>

#include "load_worker.h"

void LoadWorker::run() {
    
    // Check Member Variables
    
    if (m_File == NULL) {
        emit LoadWorker::sig_Done();
        return;
    }
    
    // Open File
    
    if (!m_File->isOpen() && !m_File->open(QFile::OpenModeFlag::ReadOnly)) {
        
        qDebug() << "File couldn't be open...";
        
        QFile::FileError error_code = m_File->error();
        
        emit LoadWorker::sig_Error(error_code);
        emit LoadWorker::sig_Done();
        
        return;
    }
    
    quint64 read_bytes = 0;
    
    // Read File
    
    quint64 chunk_size = this->calc_ChunkSize(m_File->size());
    
    while (!m_File->atEnd()) {
        
        QByteArray chunk = m_File->read(chunk_size);
        
        QFile::FileError error_code = m_File->error();
        
        if (error_code != QFile::FileError::NoError) {
            
            m_File->close();
            
            emit LoadWorker::sig_Error(error_code);
            emit LoadWorker::sig_Done();
            
            return;
        }
        
        read_bytes += chunk.size();
        
        quint8 progress = (double(read_bytes) / m_File->size()) * 100;
        
        emit LoadWorker::sig_Read(chunk);
        emit LoadWorker::sig_Progressed(progress);
        
        this->usleep(1000);
    }
    
    qDebug() << "File read completely...";
    
    m_File->close();
    
    emit LoadWorker::sig_Done();
}
