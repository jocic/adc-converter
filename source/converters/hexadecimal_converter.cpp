#include <QDebug>

#include "hexadecimal_converter.h"

QString HexadecimalConverter::toDecimal(QString& input) {
    
    if (input.size() == 0) {
        return "";
    }
    
    quint64 value;
    qint64  value_sig;
    QString output;
    
    value = input.toULongLong(NULL, 16);
    
    if (m_Signed) {
        
        if (input.size() <= 2) {
            value_sig = qint8(value);
        } else if (input.size() <= 4) {
            value_sig = qint16(value);
        } else if (input.size() <= 8) {
            value_sig = qint32(value);
        } else if (input.size() <= 16) {
            value_sig = qint64(value);
        } else {
            value_sig = 0;
        }
        
        output = QString::asprintf("%lld", value_sig);
    }
    else {
        output = QString::asprintf("%lld", value);
    }
    
    qDebug() << "Hex to Dec: Input=" << input
             << "Signed =" << m_Signed
             << "Output =" << output;
    
    return output;
}

QString HexadecimalConverter::convert(QString& input) {
    
    if (m_Type == HexadecimalConverter::Type::DEC) {
        return this->toDecimal(input);
    }
    
    return input;
}
