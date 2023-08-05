#include <QDebug>

#include "dec_converter.h"

QString DecConverter::toHexadecimal(QString& input) {
    
    if (input.size() == 0) {
        return "";
    }
    
    quint64 value;
    qint64  value_sig;
    QString output;
    
    if (input.size() > 0) {
        
        if (input.front() == '-' && !m_Signed) {
            input.erase(input.begin(), input.begin() + 1);
        }
        
        value_sig = input.toLongLong(NULL, 10);
        
        if (m_Signed) {
            
            if (-128 <= value_sig) {
                output = QString::asprintf("%02X", quint8(value_sig));
            } else if (-32768 <= value_sig) {
                output = QString::asprintf("%04X", quint16(value_sig));
            }  else if (-2147483648 <= value_sig) {
                output = QString::asprintf("%08X", quint32(value_sig));
            } else {
                output  = QString::asprintf("%08X", quint32((value_sig >> 32) & 0xFFFFFFFFFFFFFFFF));
                output += QString::asprintf("%08X", quint32((value          ) & 0xFFFFFFFFFFFFFFFF));
            } 
        }
        else {
            
            value = input.toULongLong(NULL, 10);
            
            while (value > 0) {
                output = QString::asprintf("%02X", (value & 0xFF)) + output;
                value >>= 8;
            }
        }
        
        if (output.size() == 0) {
            output = "00";
        }
    }
    
    qDebug() << "Dec to Hex: Input=" << input
             << "Signed =" << m_Signed
             << "Output =" << output;
    
    return output;
}

QString DecConverter::convert(QString& input) {
    
    if (m_Type == DecConverter::Type::HEX) {
        return this->toHexadecimal(input);
    }
    
    return input;
}
