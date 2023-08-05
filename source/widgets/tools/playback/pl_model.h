#ifndef ADC_TOL_PL_MODEL_H

#define ADC_TOL_PL_MODEL_H

#include "mvc/abstract_model.h"

class PlModel : public AbstractModel {
    
    public:
        
        static const QString FIELD_PLAYBACK_TIME;
        
        qreal get_PlaybackTime();
        void set_PlaybackTime(qreal value);
};

#endif
