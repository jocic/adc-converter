#include "reference_model.h"

const QString ReferenceModel::FIELD_POSITIVE = "txt_Positive";
const QString ReferenceModel::FIELD_NEGATIVE = "txt_Negative";
const QString ReferenceModel::FIELD_CONVERT  = "cb_Convert";

quint16 ReferenceModel::get_Positive() {
    
    QString value = this->get(FIELD_POSITIVE);
    
    return value.toUInt(NULL, 10);
}

void ReferenceModel::set_Positive(quint16 value) {
    
    QString new_value = QString::asprintf("%d", value);
    
    this->set(FIELD_POSITIVE, new_value);
    
    emit ReferenceModel::sig_Model_Updated(FIELD_POSITIVE, new_value);
}

void ReferenceModel::set_Positive(QString value) {
    
    this->set(FIELD_POSITIVE, value);
    
    emit ReferenceModel::sig_Model_Updated(FIELD_POSITIVE, value);
}

quint16 ReferenceModel::get_Negative() {
    
    QString value = this->get(FIELD_NEGATIVE);
    
    return value.toUInt(NULL, 10);
}

void ReferenceModel::set_Negative(quint16 value) {
    
    QString new_value = QString::asprintf("%d", value);
    
    this->set(FIELD_NEGATIVE, new_value);
    
    emit ReferenceModel::sig_Model_Updated(FIELD_NEGATIVE, new_value);
}

void ReferenceModel::set_Negative(QString value) {
    
    this->set(FIELD_NEGATIVE, value);
    
    emit ReferenceModel::sig_Model_Updated(FIELD_NEGATIVE, value);
}

bool ReferenceModel::get_Convert() {
    
    QString value = this->get(FIELD_CONVERT);
    
    return value == "true";
}

void ReferenceModel::set_Convert(bool value) {
    
    QString new_value = value ? "true" : "false";
    
    this->set(FIELD_CONVERT, new_value);
    
    emit ReferenceModel::sig_Model_Updated(FIELD_CONVERT, new_value);
}

void ReferenceModel::set_Convert(QString value) {
    
    this->set(FIELD_CONVERT, value);
    
    emit ReferenceModel::sig_Model_Updated(FIELD_CONVERT, value);
}
