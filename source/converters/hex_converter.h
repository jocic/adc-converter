#ifndef ADC_CONV_HEX_CONVERTER_H

#define ADC_CONV_HEX_CONVERTER_H

#include "abstract_converter.h"

class HexConverter : public AbstractConverter {
    
    private:
        QString toDecimal(QString& input);
    
    public:
        QString convert(QString& input) override;
};

#endif
