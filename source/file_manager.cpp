#include <QDebug>
#include <QMessageBox>

#include "file_manager.h"

FileManager::FileManager() {
    
    m_Buffer  = NULL;
    m_Popover = NULL;
    m_Worker  = NULL;
}

FileManager::~FileManager() {
    
    delete m_Buffer;
    delete m_Popover;
    delete m_Worker;
}

QByteArray* FileManager::get_Buffer() {
    return m_Buffer;
}

void FileManager::set_Buffer(QByteArray* buf) {
    
    if (buf != NULL) {
        delete m_Buffer;
        m_Buffer = buf;
    }
}

void FileManager::get_Chunk(QByteArray& buf, quint64 off, quint64 len) {
    
    if (off < 0 || m_Buffer == NULL) {
        return;
    }
    
    quint64 i = off;
    quint64 j = off + len;
    
    while (i < j && i < m_Buffer->size()) {
        buf.push_back(m_Buffer->at(i++));
    }
}

ProcessingPopover* FileManager::get_Popover() {
    return m_Popover;
}

void FileManager::set_Popover(ProcessingPopover* pop) {
    
    if (pop != NULL) {
        delete m_Popover;
        m_Popover = pop;
    }
}

AbstractWorker* FileManager::get_Worker() {
    return m_Worker;
}

void FileManager::set_Worker(FileWorker* wrk) {
    
    if (wrk != NULL) {
        delete m_Worker;
        m_Worker = wrk;
    }
}

bool FileManager::is_Selected() {
    return this->result() == QFileDialog::DialogCode::Accepted;
}

void FileManager::clear() {
    
    if (m_Buffer != NULL) {
        m_Buffer->clear();
    }
}

void FileManager::on_Error(QFile::FileError error) {
    
    qDebug() << "Handled error signal...";
    
    // Does nothing...
}

void FileManager::on_Abort() {
    
    qDebug() << "Handled abort signal...";
    
    if (m_Worker != NULL) {
    
        if (m_Worker->isRunning()) {
            m_Worker->terminate();
        }
    }
}

void FileManager::on_Done() {
    
    qDebug() << "Handled done signal...";
    
    if (m_Popover != NULL) {
        m_Popover->setVisible(false);
    }
}

void FileManager::on_Write(QByteArray chunk) {
    
    static QMessageBox* alert = new QMessageBox();
    
    qDebug() << "Handled write signal...";
    
    if (m_Buffer == NULL || m_Worker == NULL || m_Popover == NULL) {
        qDebug() << "Couldn't handle write signal...";
        return;
    }
    
    alert->setWindowTitle("I/O Warning");
    alert->setText("Files are read and temporarily stored in RAM. "
        "To prevent a crash, or a potential system failure, "
        "files exceeding a certain size are only partially loaded. "
        "You can disable this safety feature in options.");
    
    if (m_Buffer->size() <= 256e6) {
        *m_Buffer += chunk;
    }
    else {
        
        if (m_Worker->isRunning()) {
            m_Worker->terminate();
        }
        
        m_Popover->setVisible(false);
        
        if (!alert->isVisible()) {
            alert->exec();
        }
    }
}

void FileManager::on_Read(QByteArray& buffer, quint64 offset, quint64 length) {
    this->get_Chunk(buffer, offset, length);
}
