#include "abstract_worker.h"

QFile* AbstractWorker::get_File() {
    return m_File;
}

void AbstractWorker::set_File(QFile* file) {
    
    if (file != NULL) {
        m_File = file;
    }
}

QByteArray* AbstractWorker::get_Buffer() {
    return m_Buffer;
}

void AbstractWorker::set_Buffer(QByteArray* buffer) {
    
    if (buffer != NULL) {
        m_Buffer = buffer;
    }
}
