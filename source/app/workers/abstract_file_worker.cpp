#include <QDebug>

#include "abstract_file_worker.h"

QFile* AbstractFileWorker::get_File() {
    return m_File;
}

void AbstractFileWorker::set_File(QFile* file) {
    
    if (file != NULL) {
        m_File = file;
    }
}

QByteArray* AbstractFileWorker::get_Buffer() {
    return m_Buffer;
}

void AbstractFileWorker::set_Buffer(QByteArray* buffer) {
    
    if (buffer != NULL) {
        m_Buffer = buffer;
    }
}

quint64 AbstractFileWorker::calc_ChunkSize(quint64 size) {
    
    quint64 chunk_size = 1;
    
    if (size < 10e6) {
        chunk_size = size / 100;
    } else if (size < 100e6) {
        chunk_size = size / 1000;
    } else {
        chunk_size = size / 10000;
    }
    
    chunk_size += (512 - (chunk_size % 512));
    
    qDebug() << "Calculated chunk size of " << chunk_size
        << " for " << size;
    
    return chunk_size;
}
