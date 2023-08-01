#include "ref_model.h"

const QString RefModel::FIELD_POSITIVE = "txt_Positive";
const QString RefModel::FIELD_NEGATIVE = "txt_Negative";

quint16 RefModel::get_Positive() {
    
    QString value = this->get(FIELD_POSITIVE);
    
    return value.toUInt(NULL, 10);
}

void RefModel::set_Positive(quint16 value) {
    
    QString new_value = QString::asprintf("%d", value);
    
    this->set(FIELD_POSITIVE, new_value);
    
    emit RefModel::sig_Model_Updated(FIELD_POSITIVE, new_value);
}

quint16 RefModel::get_Negative() {
    
    QString value = this->get(FIELD_NEGATIVE);
    
    return value.toUInt(NULL, 10);
}

void RefModel::set_Negative(quint16 value) {
    
    QString new_value = QString::asprintf("%d", value);
    
    this->set(FIELD_NEGATIVE, new_value);
    
    emit RefModel::sig_Model_Updated(FIELD_NEGATIVE, new_value);
}
