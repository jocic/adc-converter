#include <QDebug>

#include "file_worker.h"

QFile* FileWorker::get_File() {
    return m_File;
}

void FileWorker::set_File(QFile* file) {
    
    if (file != NULL) {
        m_File = file;
    }
}

quint64 FileWorker::get_OptimalChunkSize() {
    
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
