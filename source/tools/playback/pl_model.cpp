#include "pl_model.h"

const QString PlModel::FIELD_PLAYBACK_TIME = "slide_PlaybackTime";

qreal PlModel::get_PlaybackTime() {
    
    QString value = this->get(FIELD_PLAYBACK_TIME);
    
    return value.toFloat(NULL);
}

void PlModel::set_PlaybackTime(qreal value) {
    
    QString new_value = QString::asprintf("%f", value);
    
    this->set(FIELD_PLAYBACK_TIME, new_value);
    
    emit PlModel::sig_Model_Updated(FIELD_PLAYBACK_TIME, new_value);
}
