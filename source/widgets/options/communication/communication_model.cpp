#include "communication_model.h"

const QString CommunicationModel::FIELD_PORT       = "cmb_Port";
const QString CommunicationModel::FIELD_MODE       = "cmb_Mode";
const QString CommunicationModel::FIELD_ENDIANNESS = "cmb_Endianness";

QString CommunicationModel::get_Port() {
    
    QString value = this->get(FIELD_PORT);
    
    return value;
}

void CommunicationModel::setPort(QString value) {
    
    
}

CommunicationModel::Mode CommunicationModel::get_Mode() {
    
    QString value = this->get(FIELD_MODE);
    
    if (value == "Text") {
        return CommunicationModel::Mode::ModeText;
    } else if (value == "Binary") {
        return CommunicationModel::Mode::ModeBinary;
    }
    
    return CommunicationModel::Mode::ModeUnknown;
}

void CommunicationModel::set_Mode(QString value) {
    
}

void CommunicationModel::set_Mode(CommunicationModel::Mode value) {
    
}

CommunicationModel::Endianness CommunicationModel::get_Endianness() {
    return CommunicationModel::Endianness::EndiannessUnknown;
}

void CommunicationModel::set_Endianness(QString value) {
    
}

void CommunicationModel::set_Endianness(CommunicationModel::Endianness value) {
    
}
