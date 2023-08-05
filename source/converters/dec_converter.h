#ifndef ADC_CONV_DEC_CONVERTER_H

#define ADC_CONV_DEC_CONVERTER_H

#include "abstract_converter.h"

class DecConverter : public AbstractConverter {
    
    private:
        QString toHexadecimal(QString& input);
    
    public:
        QString convert(QString& input) override;
};

#endif
