#ifndef ADC_VIEWS_SAMPLES_MODEL_H

#define ADC_VIEWS_SAMPLES_MODEL_H

#include "mvc/abstract_model.h"

class SamplesModel : public AbstractModel {
    
    public:
        
        static const QString FIELD_PREV;
        static const QString FIELD_NEXT;
        static const QString FIELD_OFFSET_START;
        static const QString FIELD_RANGE_SPAN;
        static const QString FIELD_OFFSET;
        
        quint64 get_OffsetStart();
        void set_OffsetStart(QString value);
        void set_OffsetStart(quint64 value);
        quint64 get_RangeSpan();
        void set_RangeSpan(QString value);
        void set_RangeSpan(quint64 value);
};

#endif
