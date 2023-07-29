#include "sr_model.h"

const QString SrModel::FIELD_SAMPLE_RATE = "txt_SampleRate";

quint32 SrModel::get_SampleRate() {
    
    QString value = this->get(FIELD_SAMPLE_RATE);
    
    return value.toUInt(NULL, 10);
}

void SrModel::set_SampleRate(quint32 value) {
    
    QString new_value = QString::asprintf("%d", value);
    
    this->set(FIELD_SAMPLE_RATE, new_value);
    
    emit SrModel::sig_Model_Updated(FIELD_SAMPLE_RATE, new_value);
}
