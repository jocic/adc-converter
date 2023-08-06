#include "decimal_model.h"

const QString DecimalModel::FIELD_DECIMAL     = "txt_Decimal";
const QString DecimalModel::FIELD_HEXADECIMAL = "txt_Hexadecimal";

QString DecimalModel::get_Decimal() {
    
    QString value = this->get(FIELD_DECIMAL);
    
    return value;
}

void DecimalModel::set_Decimal(QString value) {
    
    this->set(FIELD_DECIMAL, value);
    
    emit DecimalModel::sig_Model_Updated(FIELD_DECIMAL, value);
}

void DecimalModel::set_Decimal(quint32 value) {
    
    QString new_value = QString::asprintf("%u", value);
    
    this->set(FIELD_DECIMAL, new_value);
    
    emit DecimalModel::sig_Model_Updated(FIELD_DECIMAL, new_value);
}

QString DecimalModel::get_Hexadecimal() {
    
    QString value = this->get(FIELD_HEXADECIMAL);
    
    return value;
}

void DecimalModel::set_Hexadecimal(QString value) {
    
    this->set(FIELD_HEXADECIMAL, value);
    
    emit DecimalModel::sig_Model_Updated(FIELD_HEXADECIMAL, value);
}
