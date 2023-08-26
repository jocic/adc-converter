#include <QMutexLocker>

#include "app_core.h"

AppCore* AppCore::M_INSTANCE = NULL;
QMutex   AppCore::M_MUTEX;

AppCore* AppCore::get_Instance() {
    
    QMutexLocker locker(&M_MUTEX);
    
    if (M_INSTANCE == NULL) {
        M_INSTANCE = new AppCore();
    }
    
    return M_INSTANCE;
}

AppCore::AppCore() {
    
    m_Buffer = new QByteArray();
    
    m_DataReceiver  = new DataReceiver();
    m_TextProcessor = new TextProcessor();
}

QByteArray* AppCore::get_Buffer() {
    return m_Buffer;
}

DataReceiver* AppCore::get_DataReceiver() {
    return m_DataReceiver;
}

TextProcessor* AppCore::get_TextProcessor() {
    return m_TextProcessor;
}

void AppCore::get_Chunk(QByteArray& buf, quint64 off, quint64 len) {
    
    if (off < 0 || m_Buffer == NULL) {
        return;
    }
    
    quint64 i = off;
    quint64 j = off + len;
    
    while (i < j && i < m_Buffer->size()) {
        buf.push_back(m_Buffer->at(i++));
    }
}
