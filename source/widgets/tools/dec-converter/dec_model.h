#ifndef ADC_TOOLS_DEC_MODEL

#define ADC_TOOLS_DEC_MODEL

#include "mvc/abstract_model.h"

class DecModel : public AbstractModel {
    
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
