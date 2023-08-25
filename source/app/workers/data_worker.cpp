#include "data_worker.h"

DataWorker::DataWorker() {
    
    m_BufferSize  = 1024;
    m_BaudRate    = QSerialPort::Baud19200;
    m_ParityBit   = QSerialPort::NoParity;
    m_DataBits    = QSerialPort::Data8;
    m_StopBits    = QSerialPort::OneStop;
    m_FlowControl = QSerialPort::NoFlowControl;
    
    m_SerialPort = new QSerialPort();
}

void DataWorker::set_ComPort(QString& port) {
    m_ComPort = port;
}

void DataWorker::run() {
    
    m_SerialPort->setPortName(m_ComPort);
    m_SerialPort->setBaudRate(m_BaudRate);
    m_SerialPort->setParity(m_ParityBit);
    m_SerialPort->setDataBits(m_DataBits);
    m_SerialPort->setStopBits(m_StopBits);
    m_SerialPort->setReadBufferSize(m_BufferSize);
    
    m_SerialPort->open(QSerialPort::ReadWrite);
    
    if (m_SerialPort->isOpen()) {
        
        QByteArray buffer;
        
        while (true) {
            
            if (m_SerialPort->bytesAvailable()) {
                buffer = m_SerialPort->readAll();
                emit DataWorker::sig_Read(buffer);
            }
        }
    }
}
