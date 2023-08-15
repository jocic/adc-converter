#ifndef ADC_CONVERTERS_ABSTRACT_CONVERTER_H

#define ADC_CONVERTERS_ABSTRACT_CONVERTER_H

#include <QObject>

class AbstractConverter : public QObject {
    
    Q_OBJECT
    
    public:
        
        enum Type {
            HEX = 0,
            DEC = 1
        };
        
        Q_ENUM(Type)
        
        void set_Signed(bool value);
        bool get_Signed();
        void set_ConversionType(Type value);
        Type get_ConversionType();
        virtual QString convert(QString& input) = 0;
    
    protected:
        bool m_Signed;
        Type m_Type;
};

#endif
