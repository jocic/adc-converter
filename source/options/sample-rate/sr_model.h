#ifndef ADC_OPTIONS_SR_MODEL

#define ADC_OPTIONS_SR_MODEL

#include "mvc/abstract_model.h"

class SrModel : public AbstractModel {
    
    public:
        
        static const QString FIELD_SAMPLE_RATE;
        
        quint32 get_SampleRate();
        void set_SampleRate(quint32 value);
};

#endif
