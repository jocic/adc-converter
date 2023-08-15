#ifndef ADC_WIDGETS_STREAM_MODEL_H

#define ADC_WIDGETS_STREAM_MODEL_H

#include "app/mvc/abstract_model.h"

class StreamModel : public AbstractModel {
    
    public:
        
        static const QString FIELD_SAMPLE_RATE;
        static const QString FIELD_BITS_PER_SAMPLE;
        static const QString FIELD_SIGNED;
        
        quint64 get_SampleRate();
        void set_SampleRate(quint64 value);
        quint8 get_BitsPerSample();
        void set_BitsPerSample(quint8 value);
        bool get_Signed();
        void set_Signed(bool value);
};

#endif
