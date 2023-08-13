#ifndef ADC_WIDGETS_PLAYBACK_MODEL_H

#define ADC_WIDGETS_PLAYBACK_MODEL_H

#include "mvc/abstract_model.h"

class PlaybackModel : public AbstractModel {
    
    public:
        
        static const QString FIELD_PLAYBACK_TIME;
        static const QString FIELD_TOGGLE;
        static const QString FIELD_EXPORT;
        
        qreal get_PlaybackTime();
        void set_PlaybackTime(qreal value);
};

#endif
