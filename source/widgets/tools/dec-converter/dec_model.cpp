#include "dec_model.h"

const QString DecModel::FIELD_DECIMAL     = "txt_Decimal";
const QString DecModel::FIELD_HEXADECIMAL = "txt_Hexadecimal";

QString DecModel::get_Decimal() {
    
    QString value = this->get(FIELD_DECIMAL);
    
    return value;
}

void DecModel::set_Decimal(QString value) {
    
    this->set(FIELD_DECIMAL, value);
    
    emit DecModel::sig_Model_Updated(FIELD_DECIMAL, value);
}

void DecModel::set_Decimal(quint32 value) {
    
    QString new_value = QString::asprintf("%u", value);
    
    this->set(FIELD_DECIMAL, new_value);
    
    emit DecModel::sig_Model_Updated(FIELD_DECIMAL, new_value);
}

QString DecModel::get_Hexadecimal() {
    
    QString value = this->get(FIELD_HEXADECIMAL);
    
    return value;
}

void DecModel::set_Hexadecimal(QString value) {
    
    this->set(FIELD_HEXADECIMAL, value);
    
    emit DecModel::sig_Model_Updated(FIELD_HEXADECIMAL, value);
}
