#include "bps_model.h"

const QString BpsModel::FIELD_BITS_PER_SAMPLE = "comb_BitsPerSample";
const QString BpsModel::FIELD_SIGNED          = "check_Signed";

quint8 BpsModel::get_BitsPerSample() {
    
    QString value = this->get(FIELD_BITS_PER_SAMPLE);
    
    return value.toUInt(NULL, 10);
}

void BpsModel::set_BitsPerSample(quint8 value) {
    
    QString new_value = QString::asprintf("%d", value);
    
    this->set(FIELD_BITS_PER_SAMPLE, new_value);
    
    emit BpsModel::sig_Model_Updated(FIELD_BITS_PER_SAMPLE, new_value);
}

bool BpsModel::get_Signed() {
    
    QString value = this->get(FIELD_SIGNED);
    
    return (value == "true") ? true : false;
}

void BpsModel::set_Signed(bool value) {
    
    QString new_value = value ? "true" : "false";
    
    this->set(FIELD_SIGNED, new_value);
    
    emit BpsModel::sig_Model_Updated(FIELD_SIGNED, new_value);
}
