#include "load_worker.h"

void LoadWorker::start(QFile* file, Priority priority) {
    
    m_File = file;
    
    QThread::start();
}

void LoadWorker::stop() {
    
}

void LoadWorker::pause() {
    
}

void LoadWorker::run() {
    
    if (!m_File->isOpen() && !m_File->open(QFile::OpenModeFlag::ReadOnly)) {
        qDebug() << "File couldn't be open...";
        emit LoadWorker::sig_Error(ErrorFlags::ERR_OPEN);
        return;
    }
    
    while (!m_File->atEnd()) {
        QByteArray chunk = m_File->read(2048);
        emit LoadWorker::sig_Chunk_Read(m_File, chunk);
    }
    
    qDebug() << "File read completely...";
}
