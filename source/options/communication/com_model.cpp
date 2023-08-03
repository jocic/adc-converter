#include "com_model.h"

const QString ComModel::FIELD_PORT = "cmb_Port";
const QString ComModel::FIELD_MODE = "cmb_Mode";

QString ComModel::get_Port() {
    
    QString value = this->get(FIELD_PORT);
    
    return value;
}

void ComModel::setPort(QString value) {
    
    
}

ComModel::Mode ComModel::get_Mode() {
    
    QString value = this->get(FIELD_MODE);
    
    if (value == "Text") {
        return ComModel::Mode::Text;
    } else if (value == "Binary") {
        return ComModel::Mode::Binary;
    }
    
    return ComModel::Mode::Unknown;
}

void ComModel::set_Mode(QString value) {
    
}

void ComModel::set_Mode(ComModel::Mode value) {
    
}
