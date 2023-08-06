#ifndef ADC_WIDGETS_SERIAL_MODEL_H

#define ADC_WIDGETS_SERIAL_MODEL_H

#include <QSerialPort>

#include "mvc/abstract_model.h"

class SerialModel : public AbstractModel {
    
    public:
        
        static const QString FIELD_BAUD_RATE;
        static const QString FIELD_PARITY_BITS;
        static const QString FIELD_DATA_BITS;
        static const QString FIELD_STOP_BITS;
        static const QString FIELD_FLOW_CONTROL;
        
        QSerialPort::BaudRate get_BaudRate();
        void set_BaudRate(QSerialPort::BaudRate value);
        QSerialPort::Parity get_ParityBit();
        void set_ParityBit(QSerialPort::Parity value);
        QSerialPort::DataBits get_DataBits();
        void set_DataBits(QSerialPort::DataBits value);
        QSerialPort::StopBits get_StopBits();
        void set_StopBits(QSerialPort::StopBits value);
        QSerialPort::FlowControl get_FlowControl();
        void set_FlowControl(QSerialPort::FlowControl value);
};

#endif
