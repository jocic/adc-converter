#include "hex_model.h"

const QString HexModel::FIELD_HEXADECIMAL = "txt_Hexadecimal";
const QString HexModel::FIELD_DECIMAL     = "txt_Decimal";

QString HexModel::get_Hexadecimal() {
    
    QString value = this->get(FIELD_HEXADECIMAL);
    
    return value;
}

void HexModel::set_Hexadecimal(QString value) {
    
    this->set(FIELD_HEXADECIMAL, value);
    
    emit HexModel::sig_Model_Updated(FIELD_HEXADECIMAL, value);
}

QString HexModel::get_Decimal() {
    
    QString value = this->get(FIELD_DECIMAL);
    
    return value;
}

void HexModel::set_Decimal(QString value) {
    
    this->set(FIELD_DECIMAL, value);
    
    emit HexModel::sig_Model_Updated(FIELD_DECIMAL, value);
}
