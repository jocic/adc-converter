#ifndef ADC_TOOLS_PL_MODEL

#define ADC_TOOLS_PL_MODEL

#include "mvc/abstract_model.h"

class PlModel : public AbstractModel {
    
    public:
        
        static const QString FIELD_PLAYBACK_TIME;
        
        qreal get_PlaybackTime();
        void set_PlaybackTime(qreal value);
};

#endif
