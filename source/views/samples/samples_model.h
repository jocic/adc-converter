#ifndef ADC_VIEWS_SAMPLES_MODEL_H

#define ADC_VIEWS_SAMPLES_MODEL_H

#include "app/mvc/abstract_model.h"

class SamplesModel : public AbstractModel {
    
    public:
        
        static const QString FIELD_PREV;
        static const QString FIELD_NEXT;
        static const QString FIELD_OFFSET_START;
        static const QString FIELD_RANGE_SPAN;
        static const QString FIELD_OFFSET;
        
        static const QString VALUE_BITS_PER_SAMPLE;
        static const QString VALUE_SAMPLES;
        static const QString VALUE_TIME;
        
        quint64 get_OffsetStart();
        void set_OffsetStart(QString value);
        void set_OffsetStart(quint64 value);
        quint64 get_RangeSpan();
        void set_RangeSpan(QString value);
        void set_RangeSpan(quint64 value);
        quint8 get_BitsPerSample();
        void set_BitsPerSample(quint8 value);
        void set_BitsPerSample(QString value);
};

#endif
