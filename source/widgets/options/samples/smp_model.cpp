#include "smp_model.h"

const QString SmpModel::FIELD_SAMPLE_RATE     = "txt_SampleRate";
const QString SmpModel::FIELD_BITS_PER_SAMPLE = "comb_BitsPerSample";
const QString SmpModel::FIELD_SIGNED          = "check_Signed";

quint32 SmpModel::get_SampleRate() {
    
    QString value = this->get(FIELD_SAMPLE_RATE);
    
    return value.toUInt(NULL, 10);
}

void SmpModel::set_SampleRate(quint32 value) {
    
    QString new_value = QString::asprintf("%d", value);
    
    this->set(FIELD_SAMPLE_RATE, new_value);
    
    emit SmpModel::sig_Model_Updated(FIELD_SAMPLE_RATE, new_value);
}

quint8 SmpModel::get_BitsPerSample() {
    
    QString value = this->get(FIELD_BITS_PER_SAMPLE);
    
    return value.toUInt(NULL, 10);
}

void SmpModel::set_BitsPerSample(quint8 value) {
    
    QString new_value = QString::asprintf("%d", value);
    
    this->set(FIELD_BITS_PER_SAMPLE, new_value);
    
    emit SmpModel::sig_Model_Updated(FIELD_BITS_PER_SAMPLE, new_value);
}

bool SmpModel::get_Signed() {
    
    QString value = this->get(FIELD_SIGNED);
    
    return value == "true";
}

void SmpModel::set_Signed(bool value) {
    
    QString new_value = value ? "true" : "false";
    
    this->set(FIELD_SIGNED, new_value);
    
    emit SmpModel::sig_Model_Updated(FIELD_SIGNED, new_value);
}
