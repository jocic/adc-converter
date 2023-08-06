#include "communication_model.h"

const QString CommunicationModel::FIELD_PORT = "cmb_Port";
const QString CommunicationModel::FIELD_MODE = "cmb_Mode";

QString CommunicationModel::get_Port() {
    
    QString value = this->get(FIELD_PORT);
    
    return value;
}

void CommunicationModel::setPort(QString value) {
    
    
}

CommunicationModel::Mode CommunicationModel::get_Mode() {
    
    QString value = this->get(FIELD_MODE);
    
    if (value == "Text") {
        return CommunicationModel::Mode::Text;
    } else if (value == "Binary") {
        return CommunicationModel::Mode::Binary;
    }
    
    return CommunicationModel::Mode::Unknown;
}

void CommunicationModel::set_Mode(QString value) {
    
}

void CommunicationModel::set_Mode(CommunicationModel::Mode value) {
    
}
