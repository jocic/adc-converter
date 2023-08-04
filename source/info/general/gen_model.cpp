#include "gen_model.h"

const QString GenModel::FIELD_SAMPLES  = "lbl_Samples";
const QString GenModel::FIELD_DURATION = "lbl_Duration";

quint32 GenModel::get_Samples() {
    
    QString value = this->get(FIELD_SAMPLES);
    
    return value.toULongLong(NULL, 10);
}

void GenModel::set_Samples(quint32 value) {
    
    QString new_value = QString::asprintf("%u", value);
    
    this->set(FIELD_SAMPLES, new_value);
    
    emit GenModel::sig_Model_Updated(FIELD_SAMPLES, new_value);
}

qreal GenModel::get_Duration() {
    
    QString value = this->get(FIELD_DURATION);
    
    return value.toFloat(NULL);
}

void GenModel::set_Duration(qreal value) {
    
    QString new_value = QString::asprintf("%f", value);
    
    this->set(FIELD_DURATION, new_value);
    
    emit GenModel::sig_Model_Updated(FIELD_DURATION, new_value);
}
