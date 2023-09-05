#ifndef ADC_WIDGETS_REFERENCE_MODEL_H

#define ADC_WIDGETS_REFERENCE_MODEL_H

#include "app/mvc/abstract_model.h"

class ReferenceModel : public AbstractModel {
    
    public:
    
        static const QString FIELD_POSITIVE;
        static const QString FIELD_NEGATIVE;
        static const QString FIELD_CONVERT;
        
        quint16 get_Positive();
        void set_Positive(quint16 value);
        void set_Positive(QString value);
        quint16 get_Negative();
        void set_Negative(quint16 value);
        void set_Negative(QString value);
        bool get_Convert();
        void set_Convert(bool value);
        void set_Convert(QString value);
};

#endif
