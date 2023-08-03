#ifndef ADC_OPTIONS_SER_MODEL

#define ADC_OPTIONS_SER_MODEL

#include <QSerialPort>

#include "mvc/abstract_model.h"

class SerModel : public AbstractModel {
    
    public:
        
        static const QString FIELD_PARITY_BITS;
        static const QString FIELD_DATA_BITS;
        static const QString FIELD_STOP_BITS;
        static const QString FIELD_FLOW_CONTROL;
        
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
