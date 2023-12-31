#include "abstract_model.h"

QString AbstractModel::get(QString key) {
    
    auto search = m_Attributes.find(key);
    
    if (search == m_Attributes.end()) {
        return "";
    }
    
    return search.value();
}

void AbstractModel::set(QString key, QString value, bool silent) {
    
    m_Attributes[key] = value;
    
    if (!silent) {
        emit AbstractModel::sig_Model_Updated(key, value);
    }
}

bool AbstractModel::exists(QString key) {
    
    auto search = m_Attributes.find(key);
    
    return search != m_Attributes.end();
}

void AbstractModel::clear() {
    
    m_Attributes.clear();
    
    emit AbstractModel::sig_Model_Cleared();
}
