#ifndef ADC_WIDGETS_HEXADECIMAL_MODEL_H

#define ADC_WIDGETS_HEXADECIMAL_MODEL_H

#include "app/mvc/abstract_model.h"

class HexadecimalModel : public AbstractModel {
    
    public:
    
        static const QString FIELD_HEXADECIMAL;
        static const QString FIELD_DECIMAL;
        static const QString FIELD_SIGNED;
        
        QString get_Hexadecimal();
        void set_Hexadecimal(QString value);
        QString get_Decimal();
        void set_Decimal(QString value);
        bool get_Signed();
        void set_Signed(bool value);
};

#endif
