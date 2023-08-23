#include "stream_model.h"

const QString StreamModel::FIELD_SAMPLE_RATE     = "txt_SampleRate";
const QString StreamModel::FIELD_BITS_PER_SAMPLE = "comb_BitsPerSample";
const QString StreamModel::FIELD_SIGNED          = "check_Signed";

quint64 StreamModel::get_SampleRate() {
    
    QString value = this->get(FIELD_SAMPLE_RATE);
    
    return value.toUInt(NULL, 10);
}

void StreamModel::set_SampleRate(quint64 value) {
    
    QString new_value = QString::asprintf("%d", value);
    
    this->set(FIELD_SAMPLE_RATE, new_value);
    
    emit StreamModel::sig_Model_Updated(FIELD_SAMPLE_RATE, new_value);
}

void StreamModel::set_SampleRate(QString value) {
    
    this->set(FIELD_SAMPLE_RATE, value);
    
    emit StreamModel::sig_Model_Updated(FIELD_SAMPLE_RATE, value);
}

quint8 StreamModel::get_BitsPerSample() {
    
    QString value = this->get(FIELD_BITS_PER_SAMPLE);
    
    return value.toUInt(NULL, 10);
}

void StreamModel::set_BitsPerSample(quint8 value) {
    
    QString new_value = QString::asprintf("%d", value);
    
    this->set(FIELD_BITS_PER_SAMPLE, new_value);
    
    emit StreamModel::sig_Model_Updated(FIELD_BITS_PER_SAMPLE, new_value);
}

void StreamModel::set_BitsPerSample(QString value) {
    
    this->set(FIELD_BITS_PER_SAMPLE, value);
    
    emit StreamModel::sig_Model_Updated(FIELD_BITS_PER_SAMPLE, value);
}

bool StreamModel::get_Signed() {
    
    QString value = this->get(FIELD_SIGNED);
    
    return value == "true";
}

void StreamModel::set_Signed(bool value) {
    
    QString new_value = value ? "true" : "false";
    
    this->set(FIELD_SIGNED, new_value);
    
    emit StreamModel::sig_Model_Updated(FIELD_SIGNED, new_value);
}

void StreamModel::set_Signed(QString value) {
    
    this->set(FIELD_SIGNED, value);
    
    emit StreamModel::sig_Model_Updated(FIELD_SIGNED, value);
}
