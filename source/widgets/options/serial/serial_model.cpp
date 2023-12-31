#include "serial_model.h"

const QString SerialModel::FIELD_BAUD_RATE    = "cmb_Baud";
const QString SerialModel::FIELD_PARITY_BITS  = "cmb_Parity";
const QString SerialModel::FIELD_DATA_BITS    = "cmb_Data";
const QString SerialModel::FIELD_STOP_BITS    = "cmb_Stop";
const QString SerialModel::FIELD_FLOW_CONTROL = "cmb_Flow";

QSerialPort::BaudRate SerialModel::get_BaudRate() {
    
    QString value = this->get(FIELD_BAUD_RATE);
    
    if (value == "1200") {
        return QSerialPort::BaudRate::Baud1200;
    } else if (value == "2400") {
        return QSerialPort::BaudRate::Baud2400;
    } else if (value == "4800") {
        return QSerialPort::BaudRate::Baud4800;
    } else if (value == "9600") {
        return QSerialPort::BaudRate::Baud9600;
    } else if (value == "19200") {
        return QSerialPort::BaudRate::Baud19200;
    } else if (value == "38400") {
        return QSerialPort::BaudRate::Baud38400;
    } else if (value == "57600") {
        return QSerialPort::BaudRate::Baud57600;
    }
    
    return QSerialPort::BaudRate::Baud115200;
}

void SerialModel::set_BaudRate(QSerialPort::BaudRate value) {
    
    QString new_value = "115200";
    
    if (value == QSerialPort::BaudRate::Baud1200) {
        new_value = "1200";
    } else if (value == QSerialPort::BaudRate::Baud2400) {
        new_value = "2400";
    } else if (value == QSerialPort::BaudRate::Baud4800) {
        new_value = "4800";
    } else if (value == QSerialPort::BaudRate::Baud9600) {
        new_value = "9600";
    } else if (value == QSerialPort::BaudRate::Baud19200) {
        new_value = "19200";
    } else if (value == QSerialPort::BaudRate::Baud38400) {
        new_value = "38400";
    } else if (value == QSerialPort::BaudRate::Baud57600) {
        new_value = "57600";
    }
    
    this->set(FIELD_BAUD_RATE, new_value);
    
    emit SerialModel::sig_Model_Updated(FIELD_BAUD_RATE, new_value);
}

QSerialPort::Parity SerialModel::get_ParityBit() {
    
    QString value = this->get(FIELD_PARITY_BITS);
    
    if (value == "Even") {
        return QSerialPort::Parity::EvenParity;
    } else if (value == "Odd") {
        return QSerialPort::Parity::OddParity;
    } else if (value == "Space") {
        return QSerialPort::Parity::SpaceParity;
    } else if (value == "Mark") {
        return QSerialPort::Parity::MarkParity;
    }
    
    return QSerialPort::Parity::NoParity;
}

void SerialModel::set_ParityBit(QSerialPort::Parity value) {
    
    QString new_value = "None";
    
    if (value == QSerialPort::Parity::EvenParity) {
        new_value = "Even";
    } else if (value == QSerialPort::Parity::OddParity) {
        new_value = "Odd";
    } else if (value == QSerialPort::Parity::SpaceParity) {
        new_value = "Space";
    } else if (value == QSerialPort::Parity::MarkParity) {
        new_value = "Mark";
    }
    
    this->set(FIELD_PARITY_BITS, new_value);
    
    emit SerialModel::sig_Model_Updated(FIELD_PARITY_BITS, new_value);
}

QSerialPort::DataBits SerialModel::get_DataBits() {
    
    QString value = this->get(FIELD_DATA_BITS);
    
    if (value == "5") {
        return QSerialPort::DataBits::Data5;
    } else if (value == "6") {
        return QSerialPort::DataBits::Data6;
    } else if (value == "7") {
        return QSerialPort::DataBits::Data7;
    }
    
    return QSerialPort::DataBits::Data8;
}

void SerialModel::set_DataBits(QSerialPort::DataBits value) {
    
    QString new_value = "8";
    
    if (value == QSerialPort::DataBits::Data5) {
        new_value = "5";
    } else if (value == QSerialPort::DataBits::Data6) {
        new_value = "6";
    } else if (value == QSerialPort::DataBits::Data7) {
        new_value = "7";
    }
    
    this->set(FIELD_DATA_BITS, new_value);
    
    emit SerialModel::sig_Model_Updated(FIELD_DATA_BITS, new_value);
}

QSerialPort::StopBits SerialModel::get_StopBits() {
    
    QString value = this->get(FIELD_STOP_BITS);
    
    if (value == "1/2") {
        return QSerialPort::StopBits::OneAndHalfStop;
    } else if (value == "2/1") {
        return QSerialPort::StopBits::TwoStop;
    }
    
    return QSerialPort::StopBits::OneStop;
}

void SerialModel::set_StopBits(QSerialPort::StopBits value) {
    
    QString new_value = "1/1";
    
    if (value == QSerialPort::StopBits::OneAndHalfStop) {
        new_value = "1/2";
    } else if (value == QSerialPort::StopBits::TwoStop) {
        new_value = "2/1";
    }
    
    this->set(FIELD_DATA_BITS, new_value);
    
    emit SerialModel::sig_Model_Updated(FIELD_DATA_BITS, new_value);
}

QSerialPort::FlowControl SerialModel::get_FlowControl() {
    
    QString value = this->get(FIELD_FLOW_CONTROL);
    
    if (value == "Hardware") {
        return QSerialPort::FlowControl::HardwareControl;
    } else if (value == "Software") {
        return QSerialPort::FlowControl::SoftwareControl;
    }
    
    return QSerialPort::FlowControl::NoFlowControl;
}

void SerialModel::set_FlowControl(QSerialPort::FlowControl value) {
    
    QString new_value = "None";
    
    if (value == QSerialPort::FlowControl::HardwareControl) {
        new_value = "Hardware";
    } else if (value == QSerialPort::FlowControl::SoftwareControl) {
        new_value = "Software";
    }
    
    this->set(FIELD_FLOW_CONTROL, new_value);
    
    emit SerialModel::sig_Model_Updated(FIELD_FLOW_CONTROL, new_value);
}
