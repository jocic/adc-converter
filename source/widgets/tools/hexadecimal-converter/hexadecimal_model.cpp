#include "hexadecimal_model.h"

const QString HexadecimalModel::FIELD_HEXADECIMAL = "txt_Hexadecimal";
const QString HexadecimalModel::FIELD_DECIMAL     = "txt_Decimal";
const QString HexadecimalModel::FIELD_SIGNED      = "check_Signed";

QString HexadecimalModel::get_Hexadecimal() {
    
    QString value = this->get(FIELD_HEXADECIMAL);
    
    return value;
}

void HexadecimalModel::set_Hexadecimal(QString value) {
    
    this->set(FIELD_HEXADECIMAL, value);
    
    emit HexadecimalModel::sig_Model_Updated(FIELD_HEXADECIMAL, value);
}

QString HexadecimalModel::get_Decimal() {
    
    QString value = this->get(FIELD_DECIMAL);
    
    return value;
}

void HexadecimalModel::set_Decimal(QString value) {
    
    this->set(FIELD_DECIMAL, value);
    
    emit HexadecimalModel::sig_Model_Updated(FIELD_DECIMAL, value);
}

bool HexadecimalModel::get_Signed() {
    
    QString value = this->get(FIELD_SIGNED);
    
    return value == "true";
}

void HexadecimalModel::set_Signed(bool value) {
    
    QString new_value = value ? "true" : "false";
    
    this->set(FIELD_SIGNED, new_value);
    
    emit HexadecimalModel::sig_Model_Updated(FIELD_SIGNED, new_value);
}
