#ifndef ADC_OPTIONS_BPS_MODEL

#define ADC_OPTIONS_BPS_MODEL

#include "mvc/abstract_model.h"

class BpsModel : public AbstractModel {
    
    public:
        
        static const QString FIELD_BITS_PER_SAMPLE;
        static const QString FIELD_SIGNED;
        
        quint8 get_BitsPerSample();
        void set_BitsPerSample(quint8 value);
        bool get_Signed();
        void set_Signed(bool value);
};

#endif
