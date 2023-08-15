#include "element_manager.h"

const QList<QString>& ElementManager::names() {
    
    return m_Names;
}

bool ElementManager::push(const QString& name, QWidget* element) {
    
    if (m_Elements.contains(name)) {
        return false;
    }
    
    m_Names.push_back(name);
    m_Elements.insert(name, element);
    
    return true;
}

QWidget* ElementManager::get(const QString& name) {
    
    auto search = m_Elements.find(name);
    
    if (search != m_Elements.end()) {
        return search.value();
    }
    
    return NULL;
}

void ElementManager::lock() {
    
    for (auto it = m_Elements.begin(); it != m_Elements.end(); it++) {
        it.value()->setEnabled(false);
    }
}

void ElementManager::lock(const QString& name) {
    
    auto search = m_Elements.find(name);
    
    if (search != m_Elements.end()) {
        search.value()->setEnabled(false);
    }
}

void ElementManager::unlock() {
    
    for (auto it = m_Elements.begin(); it != m_Elements.end(); it++) {
        it.value()->setEnabled(true);
    }
}

void ElementManager::unlock(const QString& name) {
    
    auto search = m_Elements.find(name);
    
    if (search != m_Elements.end()) {
        search.value()->setEnabled(true);
    }
}
