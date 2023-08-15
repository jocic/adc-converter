#ifndef ADC_CONVERTERS_HEXADECIMAL_CONVERTER_H

#define ADC_CONVERTERS_HEXADECIMAL_CONVERTER_H

#include "abstract_converter.h"

class HexadecimalConverter : public AbstractConverter {
    
    private:
        QString toDecimal(QString& input);
    
    public:
        QString convert(QString& input) override;
};

#endif
