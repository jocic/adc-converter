#include "str_model.h"

const QString StrModel::FIELD_SAMPLE_RATE     = "txt_SampleRate";
const QString StrModel::FIELD_BITS_PER_SAMPLE = "comb_BitsPerSample";
const QString StrModel::FIELD_SIGNED          = "check_Signed";

quint32 StrModel::get_SampleRate() {
    
    QString value = this->get(FIELD_SAMPLE_RATE);
    
    return value.toUInt(NULL, 10);
}

void StrModel::set_SampleRate(quint32 value) {
    
    QString new_value = QString::asprintf("%d", value);
    
    this->set(FIELD_SAMPLE_RATE, new_value);
    
    emit StrModel::sig_Model_Updated(FIELD_SAMPLE_RATE, new_value);
}

quint8 StrModel::get_BitsPerSample() {
    
    QString value = this->get(FIELD_BITS_PER_SAMPLE);
    
    return value.toUInt(NULL, 10);
}

void StrModel::set_BitsPerSample(quint8 value) {
    
    QString new_value = QString::asprintf("%d", value);
    
    this->set(FIELD_BITS_PER_SAMPLE, new_value);
    
    emit StrModel::sig_Model_Updated(FIELD_BITS_PER_SAMPLE, new_value);
}

bool StrModel::get_Signed() {
    
    QString value = this->get(FIELD_SIGNED);
    
    return value == "true";
}

void StrModel::set_Signed(bool value) {
    
    QString new_value = value ? "true" : "false";
    
    this->set(FIELD_SIGNED, new_value);
    
    emit StrModel::sig_Model_Updated(FIELD_SIGNED, new_value);
}
