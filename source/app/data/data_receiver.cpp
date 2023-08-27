#include "app/data/data_receiver.h"

DataReceiver::DataReceiver() {
    
    // Serial Port
    
    m_SerialPort = new QSerialPort();
    
    m_SerialPort->setBaudRate(QSerialPort::BaudRate::Baud19200);
    m_SerialPort->setDataBits(QSerialPort::DataBits::Data8);
    m_SerialPort->setStopBits(QSerialPort::StopBits::OneStop);
    m_SerialPort->setParity(QSerialPort::Parity::NoParity);
    m_SerialPort->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
    
    // Read Timer
    
    m_ReadTimer = new QTimer();
    
    connect(m_ReadTimer, &QTimer::timeout,
        this, &DataReceiver::on_ReadInterval);
    
    // Simulation Timer
    
    m_SimTimer = new QTimer();
    
    connect(m_SimTimer, &QTimer::timeout,
        this, &DataReceiver::on_SimInterval);
}

QSerialPort* DataReceiver::serialPort() {
    return m_SerialPort;
}

void DataReceiver::start(bool simulate) {
    
    if (simulate) {
        
        if (!m_SimTimer->isActive()) {
            m_SimTimer->start();
        }
    }
    else {
        
        m_SerialPort->open(QSerialPort::OpenModeFlag::ReadOnly);
        
        if (m_SerialPort->isOpen() && !m_ReadTimer->isActive()) {
            m_ReadTimer->start();
        }
    }
    
    emit DataReceiver::sig_Started();
}

void DataReceiver::stop() {
    
    if (m_ReadTimer->isActive()) {
        m_ReadTimer->stop();
    }
    
    if (m_SimTimer->isActive()) {
        m_SimTimer->stop();
    }
    
    emit DataReceiver::sig_Stopped();
}

bool DataReceiver::isRunning() {
    return m_ReadTimer->isActive() || m_SimTimer->isActive();
}

void DataReceiver::on_ReadInterval() {
    
    if (m_SerialPort->isOpen() && m_SerialPort->isReadable()) {
       
        if (m_SerialPort->bytesAvailable()) {
            QByteArray buffer = m_SerialPort->readAll();
            emit DataReceiver::sig_BufferRead(buffer);
        }
    }
}

void DataReceiver::on_SimInterval() {
    
    // TBI - load a file
}
