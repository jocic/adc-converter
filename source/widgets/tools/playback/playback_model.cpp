#include "playback_model.h"

const QString PlaybackModel::FIELD_PLAYBACK_TIME = "slide_PlaybackTime";

qreal PlaybackModel::get_PlaybackTime() {
    
    QString value = this->get(FIELD_PLAYBACK_TIME);
    
    return value.toFloat(NULL);
}

void PlaybackModel::set_PlaybackTime(qreal value) {
    
    QString new_value = QString::asprintf("%f", value);
    
    this->set(FIELD_PLAYBACK_TIME, new_value);
    
    emit PlaybackModel::sig_Model_Updated(FIELD_PLAYBACK_TIME, new_value);
}
