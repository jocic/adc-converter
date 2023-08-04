#ifndef ADC_TOOLS_HEX_MODEL

#define ADC_TOOLS_HEX_MODEL

#include "mvc/abstract_model.h"

class HexModel : public AbstractModel {
    
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
