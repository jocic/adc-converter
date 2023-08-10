#include "samples_model.h"

const QString SamplesModel::FIELD_PREV         = "btn_Prev";
const QString SamplesModel::FIELD_NEXT         = "btn_Next";
const QString SamplesModel::FIELD_OFFSET_START = "txt_OffsetStart";
const QString SamplesModel::FIELD_RANGE_SPAN   = "comb_RangeSpan";
const QString SamplesModel::FIELD_OFFSET       = "btn_Offset";

const QString SamplesModel::VALUE_BITS_PER_SAMPLE = "val_BitsPerSample";

const QString SamplesModel::VALUE_SAMPLES = "lbl_Samples";
const QString SamplesModel::VALUE_TIME    = "lbl_Time";

quint64 SamplesModel::get_OffsetStart() {
    
    QString value = this->get(FIELD_OFFSET_START);
    
    return value.toUInt(NULL, 10);
}

void SamplesModel::set_OffsetStart(QString value) {
    
    this->set(FIELD_OFFSET_START, value);
    
    emit SamplesModel::sig_Model_Updated(FIELD_OFFSET_START, value);
}

void SamplesModel::set_OffsetStart(quint64 value) {
    
    QString new_value = QString::asprintf("%llu", value);
    
    this->set(FIELD_OFFSET_START, new_value);
    
    emit SamplesModel::sig_Model_Updated(FIELD_OFFSET_START, new_value);
}

quint64 SamplesModel::get_RangeSpan() {
    
    QString value = this->get(FIELD_RANGE_SPAN);
    
    return value.toUInt(NULL, 10);
}

void SamplesModel::set_RangeSpan(QString value) {
    
    this->set(FIELD_RANGE_SPAN, value);
    
    emit SamplesModel::sig_Model_Updated(FIELD_RANGE_SPAN, value);
}

void SamplesModel::set_RangeSpan(quint64 value) {
    
    QString new_value = QString::asprintf("%llu", value);
    
    this->set(FIELD_RANGE_SPAN, new_value);
    
    emit SamplesModel::sig_Model_Updated(FIELD_RANGE_SPAN, new_value);
}

quint8 SamplesModel::get_BitsPerSample() {
    
    QString value = this->get(VALUE_BITS_PER_SAMPLE);
    
    return value.toUInt(NULL, 10);
}

void SamplesModel::set_BitsPerSample(quint8 value) {
    
    QString new_value = QString::asprintf("%u", value);
    
    this->set(VALUE_BITS_PER_SAMPLE, new_value);
    
    emit SamplesModel::sig_Model_Updated(VALUE_BITS_PER_SAMPLE, new_value);
}

void SamplesModel::set_BitsPerSample(QString value) {
    
    this->set(VALUE_BITS_PER_SAMPLE, value);
    
    emit SamplesModel::sig_Model_Updated(VALUE_BITS_PER_SAMPLE, value);
}
