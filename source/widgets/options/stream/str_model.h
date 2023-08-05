#ifndef ADC_OPT_STR_MODEL_H

#define ADC_OPT_STR_MODEL_H

#include "mvc/abstract_model.h"

class StrModel : public AbstractModel {
    
    public:
        
        static const QString FIELD_SAMPLE_RATE;
        static const QString FIELD_BITS_PER_SAMPLE;
        static const QString FIELD_SIGNED;
        
        quint32 get_SampleRate();
        void set_SampleRate(quint32 value);        
        quint8 get_BitsPerSample();
        void set_BitsPerSample(quint8 value);
        bool get_Signed();
        void set_Signed(bool value);
};

#endif
