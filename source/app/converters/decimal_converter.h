#ifndef ADC_CONVERTERS_DECIMAL_CONVERTER_H

#define ADC_CONVERTERS_DECIMAL_CONVERTER_H

#include "abstract_converter.h"

class DecimalConverter : public AbstractConverter {
    
    private:
        QString toHexadecimal(QString& input);
    
    public:
        QString convert(QString& input) override;
};

#endif
