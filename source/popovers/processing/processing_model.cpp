#include "processing_model.h"

const QString ProcessingModel::FIELD_HEXADECIMAL = "txt_Hexadecimal";
const QString ProcessingModel::FIELD_DECIMAL     = "txt_Decimal";
const QString ProcessingModel::FIELD_SIGNED      = "check_Signed";

QString ProcessingModel::get_Hexadecimal() {
    
    QString value = this->get(FIELD_HEXADECIMAL);
    
    return value;
}

void ProcessingModel::set_Hexadecimal(QString value) {
    
    this->set(FIELD_HEXADECIMAL, value);
    
    emit ProcessingModel::sig_Model_Updated(FIELD_HEXADECIMAL, value);
}

QString ProcessingModel::get_Decimal() {
    
    QString value = this->get(FIELD_DECIMAL);
    
    return value;
}

void ProcessingModel::set_Decimal(QString value) {
    
    this->set(FIELD_DECIMAL, value);
    
    emit ProcessingModel::sig_Model_Updated(FIELD_DECIMAL, value);
}

bool ProcessingModel::get_Signed() {
    
    QString value = this->get(FIELD_SIGNED);
    
    return value == "true";
}

void ProcessingModel::set_Signed(bool value) {
    
    QString new_value = value ? "true" : "false";
    
    this->set(FIELD_SIGNED, new_value);
    
    emit ProcessingModel::sig_Model_Updated(FIELD_SIGNED, new_value);
}
