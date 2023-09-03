#include <QDebug>

#include "app/data/data_receiver.h"

DataReceiver::DataReceiver() {
    
    // Serial Port
    
    m_SerialPort = new QSerialPort();
    
    m_SerialPort->setBaudRate(QSerialPort::BaudRate::Baud19200);
    m_SerialPort->setDataBits(QSerialPort::DataBits::Data8);
    m_SerialPort->setStopBits(QSerialPort::StopBits::OneStop);
    m_SerialPort->setParity(QSerialPort::Parity::NoParity);
    m_SerialPort->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
    m_SerialPort->setReadBufferSize(1024);
    
    // Read Timer
    
    m_ReadTimer = new QTimer();
    
    connect(m_ReadTimer, &QTimer::timeout,
        this, &DataReceiver::on_ReadInterval);
    
    // Simulation Timer
    
    m_SimTimer = new QTimer();
    
    m_SimTimer->setInterval(100);
    
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
        } else {
            return;
        }
    }
    else {
        
        if (!m_SerialPort->isOpen()) {
            
            m_SerialPort->open(QSerialPort::OpenModeFlag::ReadOnly);
            
            if (m_SerialPort->error() != QSerialPort::SerialPortError::NoError) {
                return;
            }
        }
        
        if (!m_ReadTimer->isActive()) {
            m_ReadTimer->start();
        } else {
            return;
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
    
    m_SerialPort->close();
    
    emit DataReceiver::sig_Stopped();
}

bool DataReceiver::isRunning() {
    return m_ReadTimer->isActive() || m_SimTimer->isActive();
}

void DataReceiver::on_ReadInterval() {
    
    if (m_SerialPort->isOpen() && m_SerialPort->isReadable()) {
        
        if (m_SerialPort->bytesAvailable()) {
            
            QByteArray buffer = m_SerialPort->readAll();
            
            if (m_SerialPort->error() == QSerialPort::SerialPortError::NoError) {
                emit DataReceiver::sig_BufferRead(buffer);
            } else {
                emit DataReceiver::sig_Error();
            }
        }
    }
}

void DataReceiver::on_SimInterval() {
    
    // Generate Signal Seed
    
    static QVector<QString> signal_seed;
    static quint64          signal_index;
    
    if (signal_seed.empty()) {
        
        signal_index = 0;
        
        QString sample;
        
        qreal  x = -3.14;
        qint16 y = 0;
        qint16 n = 0;
        
        for (quint64 i = 0; i < 10000; i++) {
            
            x = -3.14;
            
            while (x <= 3.14) {
                
                n = rand() % 6000;
                
                y  = (qSin(x) * 20000) + n;
                x += 0.4F;
                
                sample = QString::asprintf("%d\r\n", y);
                
                signal_seed.push_back(sample);
            }
        }
    }
    
    // Generate Simulation Buffer
    
    QByteArray buffer;
    
    for (quint64 i = 0; i < 1024; i++) {
        
        for (const auto& c : signal_seed[signal_index].toStdString()) {
            buffer.push_back(c);
        }
        
        if (++signal_index == signal_seed.size()) {
            signal_index = 0;
        }
    }
    
    emit DataReceiver::sig_BufferRead(buffer);
}
