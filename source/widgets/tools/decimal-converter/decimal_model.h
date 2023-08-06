#ifndef ADC_WIDGETS_DECIMAL_MODEL_H

#define ADC_WIDGETS_DECIMAL_MODEL_H

#include "mvc/abstract_model.h"

class DecimalModel : public AbstractModel {
    
    public:
        
        static const QString FIELD_DECIMAL;
        static const QString FIELD_HEXADECIMAL;
        
        QString get_Decimal();
        void set_Decimal(QString value);
        void set_Decimal(quint32 value);
        QString get_Hexadecimal();
        void set_Hexadecimal(QString value);
};

#endif
