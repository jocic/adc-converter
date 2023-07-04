#include <QtMath>

#include <QDebug>
#include <QRandomGenerator>

#include "data_receiver.h"

DataReceiver::DataReceiver()
{
    this->serial_port = new QSerialPort();
}

bool DataReceiver::configure(QString port_name, quint32 baud_rate) {
    
    if (this->serial_port->isOpen()) {
        this->serial_port->close();
    }
    
    this->serial_port->setPortName(port_name);
    this->serial_port->setBaudRate(baud_rate);
    this->serial_port->setParity(QSerialPort::NoParity);
    this->serial_port->setDataBits(QSerialPort::Data8);
    this->serial_port->setStopBits(QSerialPort::OneStop);
    this->serial_port->setReadBufferSize(1024);
    
    return this->serial_port->open(QSerialPort::ReadWrite);
}

void DataReceiver::setSampleRate(quint64 sample_rate) {
    
    this->sample_rate = sample_rate;
}

void DataReceiver::setBitsPerSample(quint8 bits_per_sample, bool signed_sample) {
    
    this->bits_per_sample = bits_per_sample;
    this->signed_sample   = signed_sample;
    
    this->bytes_per_sample = this->bits_per_sample / 8;
}

void DataReceiver::run() {
    
    QByteArray       buffer;
    QVector<quint64> samples;
    quint64          sample       = 0;
    quint64          sample_count = 0;
    
    while (true) {
        
        
        if (this->serial_port->bytesAvailable()) {
            
            buffer = this->serial_port->readAll();
            
            emit this->new_data(buffer);
        }
    }
}
