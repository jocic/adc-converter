#ifndef ADC_INF_GEN_MODEL_H

#define ADC_INF_GEN_MODEL_H

#include "mvc/abstract_model.h"

class GenModel : public AbstractModel {
    
    public:
        
        static const QString FIELD_SAMPLES;
        static const QString FIELD_DURATION;
        
        quint32 get_Samples();
        void set_Samples(quint32 value);
        qreal get_Duration();
        void set_Duration(qreal value);
};

#endif
