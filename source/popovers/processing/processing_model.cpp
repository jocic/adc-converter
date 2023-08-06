#include "processing_model.h"

const QString ProcessingModel::FIELD_PROGRESS = "pb_Progress";

QString ProcessingModel::get_Progress() {
    
    QString value = this->get(FIELD_PROGRESS);
    
    return value;
}

void ProcessingModel::set_Progress(QString value) {
    
    this->set(FIELD_PROGRESS, value);
    
    emit ProcessingModel::sig_Model_Updated(FIELD_PROGRESS, value);
}

void ProcessingModel::set_Progress(quint8 value) {
    
    QString new_value = QString::asprintf("%u", value);
    
    this->set(FIELD_PROGRESS, new_value);
    
    emit ProcessingModel::sig_Model_Updated(FIELD_PROGRESS, new_value);
}
