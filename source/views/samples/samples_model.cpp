#include "samples_model.h"

const QString SamplesModel::FIELD_PREV         = "btn_Prev";
const QString SamplesModel::FIELD_NEXT         = "btn_Next";
const QString SamplesModel::FIELD_OFFSET_START = "txt_OffsetStart";
const QString SamplesModel::FIELD_RANGE_SPAN   = "comb_RangeSpan";
const QString SamplesModel::FIELD_OFFSET       = "btn_Offset";

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
    
    this->set(FIELD_OFFSET_START, new_value);
    
    emit SamplesModel::sig_Model_Updated(FIELD_RANGE_SPAN, new_value);
}
