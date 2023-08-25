#ifndef ADC_WORKERS_DATA_WORKER_H

#define ADC_WORKERS_DATA_WORKER_H

#include <QObject>
#include <QFile>
#include <QByteArray>
#include <QSerialPort>

#include "app/workers/abstract_worker.h"

class DataWorker : public AbstractWorker {
    
    Q_OBJECT
    
    private:
        
        QSerialPort::BaudRate    m_BaudRate;
        QSerialPort::Parity      m_ParityBit;
        QSerialPort::DataBits    m_DataBits;
        QSerialPort::StopBits    m_StopBits;
        QSerialPort::FlowControl m_FlowControl;
        
        quint64 m_BufferSize;
        QString m_ComPort;
        
        QSerialPort* m_SerialPort;
        
    public:
        DataWorker();
        void set_ComPort(QString& com_port);
        void run() override;
    
    signals:
        void sig_Read(QByteArray buffer);
};

#endif
