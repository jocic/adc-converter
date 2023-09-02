#include <QComboBox>

#include "app/app_mediator.h"
#include "serial_model.h"
#include "serial_controller.h"

void SerialController::on_View_Initialized(ElementManager* manager) {
    
    this->tuneTo(AppMediator::Channel::STREAM_EVENTS);
    
    //////////////////////////////
    
    this->registerField(SerialModel::FIELD_BAUD_RATE,
        QComboBox::staticMetaObject.className());
    
    this->registerField(SerialModel::FIELD_DATA_BITS,
        QComboBox::staticMetaObject.className());
    
    this->registerField(SerialModel::FIELD_STOP_BITS,
        QComboBox::staticMetaObject.className());
    
    this->registerField(SerialModel::FIELD_PARITY_BITS,
        QComboBox::staticMetaObject.className());
    
    this->registerField(SerialModel::FIELD_FLOW_CONTROL,
        QComboBox::staticMetaObject.className());
}

void SerialController::on_View_Changed() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    SerialModel*    model   = (SerialModel*)this->get_Model();
    
    //////////////////////////////
    
    // Baud Rate
    
    QComboBox* cmb_baud = (QComboBox*)manager
        ->get(SerialModel::FIELD_BAUD_RATE);
    
    quint64 baud_rate = cmb_baud->currentText().toUInt();
    
    model->set_BaudRate((QSerialPort::BaudRate)baud_rate);
    
    // Data Bits
    
    QComboBox* cmb_data = (QComboBox*)manager
        ->get(SerialModel::FIELD_DATA_BITS);
    
    quint8 data_bits = cmb_data->currentText().toUInt();
    
    model->set_DataBits((QSerialPort::DataBits)data_bits);
    
    // Stop Bits
    
    QComboBox* cmb_stop = (QComboBox*)manager
        ->get(SerialModel::FIELD_STOP_BITS);
    
    QSerialPort::StopBits stop_bits = QSerialPort::StopBits::OneStop;
    
    if (cmb_stop->currentText() == "1/1") {
        stop_bits = QSerialPort::StopBits::OneStop;
    } else if (cmb_stop->currentText() == "1/2") {
        stop_bits = QSerialPort::StopBits::OneAndHalfStop;
    } else if (cmb_stop->currentText() == "2/1") {
        stop_bits = QSerialPort::StopBits::TwoStop;
    }
    
    model->set_StopBits(stop_bits);
    
    // Parity Bit
    
    QComboBox* cmb_parity = (QComboBox*)manager
        ->get(SerialModel::FIELD_PARITY_BITS);
    
    QSerialPort::Parity parity_bit = QSerialPort::Parity::NoParity;
    
    if (cmb_parity->currentText() == "None") {
        parity_bit = QSerialPort::Parity::NoParity;
    } else if (cmb_parity->currentText() == "Even") {
        parity_bit = QSerialPort::Parity::EvenParity;
    } else if (cmb_parity->currentText() == "Odd") {
        parity_bit = QSerialPort::Parity::OddParity;
    } else if (cmb_parity->currentText() == "Space") {
        parity_bit = QSerialPort::Parity::SpaceParity;
    } else if (cmb_parity->currentText() == "Mark") {
        parity_bit = QSerialPort::Parity::MarkParity;
    }
    
    model->set_ParityBit(parity_bit);
    
    // Flow Control
    
    QComboBox* cmb_flow = (QComboBox*)manager
        ->get(SerialModel::FIELD_FLOW_CONTROL);
    
    QSerialPort::FlowControl flow_control = QSerialPort::FlowControl::NoFlowControl;
    
    if (cmb_flow->currentText() == "None") {
        flow_control = QSerialPort::FlowControl::NoFlowControl;
    } else if (cmb_flow->currentText() == "Hardware") {
        flow_control = QSerialPort::FlowControl::HardwareControl;
    } else if (cmb_flow->currentText() == "Software") {
        flow_control = QSerialPort::FlowControl::SoftwareControl;
    }
    
    model->set_FlowControl(flow_control);
    
    //////////////////////////////
    
    app_data_t data;
    
    data.ser_config.baud_rate    = (QSerialPort::BaudRate)baud_rate;
    data.ser_config.data_bits    = (QSerialPort::DataBits)data_bits;
    data.ser_config.stop_bits    = stop_bits;
    data.ser_config.parity_bit   = parity_bit;
    data.ser_config.flow_control = flow_control;
    
    emit SerialController::sig_Broadcast(
        AppMediator::Channel::SERIAL_PARAMS, data);
}

void SerialController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == SerialModel::FIELD_BAUD_RATE) {
        
        QComboBox* cmb_baud = (QComboBox*)manager
            ->get(SerialModel::FIELD_BAUD_RATE);
        
        for (int i = 0; i < cmb_baud->count(); i++) {
            if (cmb_baud->itemText(i) == value) {
                cmb_baud->setCurrentIndex(i); break;
            }
        }
    }
    else if (key == SerialModel::FIELD_DATA_BITS) {
        
        QComboBox* cmb_data = (QComboBox*)manager
            ->get(SerialModel::FIELD_DATA_BITS);
        
        for (int i = 0; i < cmb_data->count(); i++) {
            if (cmb_data->itemText(i) == value) {
                cmb_data->setCurrentIndex(i); break;
            }
        }
    }
    else if (key == SerialModel::FIELD_PARITY_BITS) {
        
        QComboBox* cmb_parity = (QComboBox*)manager
            ->get(SerialModel::FIELD_PARITY_BITS);
        
        for (int i = 0; i < cmb_parity->count(); i++) {
            if (cmb_parity->itemText(i) == value) {
                cmb_parity->setCurrentIndex(i); break;
            }
        }
    }
    else if (key == SerialModel::FIELD_STOP_BITS) {
        
        QComboBox* cmb_stop = (QComboBox*)manager
            ->get(SerialModel::FIELD_STOP_BITS);
        
        for (int i = 0; i < cmb_stop->count(); i++) {
            if (cmb_stop->itemText(i) == value) {
                cmb_stop->setCurrentIndex(i); break;
            }
        }
    }
    else if (key == SerialModel::FIELD_FLOW_CONTROL) {
        
        QComboBox* cmb_flow = (QComboBox*)manager
            ->get(SerialModel::FIELD_FLOW_CONTROL);
        
        for (int i = 0; i < cmb_flow->count(); i++) {
            if (cmb_flow->itemText(i) == value) {
                cmb_flow->setCurrentIndex(i); break;
            }
        }
    }
}

void SerialController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QComboBox* cmb_baud = (QComboBox*)manager
        ->get(SerialModel::FIELD_BAUD_RATE);
    
    for (int i = 0; i < cmb_baud->count(); i++) {
        if (cmb_baud->itemText(i) == "19200") {
            cmb_baud->setCurrentIndex(i); break;
        }
    }
    
    QComboBox* cmb_data = (QComboBox*)manager
        ->get(SerialModel::FIELD_DATA_BITS);
    
    for (int i = 0; i < cmb_data->count(); i++) {
        if (cmb_data->itemText(i) == "8") {
            cmb_data->setCurrentIndex(i); break;
        }
    }
    
    QComboBox* cmb_parity = (QComboBox*)manager
        ->get(SerialModel::FIELD_PARITY_BITS);
    
    for (int i = 0; i < cmb_parity->count(); i++) {
        if (cmb_parity->itemText(i) == "None") {
            cmb_parity->setCurrentIndex(i); break;
        }
    }
    
    QComboBox* cmb_stop = (QComboBox*)manager
        ->get(SerialModel::FIELD_STOP_BITS);
    
    for (int i = 0; i < cmb_stop->count(); i++) {
        if (cmb_stop->itemText(i) == "1/1") {
            cmb_stop->setCurrentIndex(i); break;
        }
    }
    
    QComboBox* cmb_flow = (QComboBox*)manager
        ->get(SerialModel::FIELD_FLOW_CONTROL);
    
    for (int i = 0; i < cmb_flow->count(); i++) {
        if (cmb_flow->itemText(i) == "None") {
            cmb_flow->setCurrentIndex(i); break;
        }
    }
}

void SerialController::on_Broadcast(quint64 ch, app_data_t data) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QComboBox* cmb_baud = (QComboBox*)manager
        ->get(SerialModel::FIELD_BAUD_RATE);
    
    QComboBox* cmb_data = (QComboBox*)manager
        ->get(SerialModel::FIELD_DATA_BITS);
    
    QComboBox* cmb_parity = (QComboBox*)manager
        ->get(SerialModel::FIELD_PARITY_BITS);
    
    QComboBox* cmb_stop = (QComboBox*)manager
        ->get(SerialModel::FIELD_STOP_BITS);
    
    QComboBox* cmb_flow = (QComboBox*)manager
        ->get(SerialModel::FIELD_FLOW_CONTROL);
    
    if (ch == AppMediator::Channel::STREAM_EVENTS) {
        
        if (data.event == "stream_started") {
            cmb_baud->setEnabled(false);
            cmb_data->setEnabled(false);
            cmb_parity->setEnabled(false);
            cmb_stop->setEnabled(false);
            cmb_flow->setEnabled(false);
        }
        else if (data.event == "stream_ended") {
            cmb_baud->setEnabled(true);
            cmb_data->setEnabled(true);
            cmb_parity->setEnabled(true);
            cmb_stop->setEnabled(true);
            cmb_flow->setEnabled(true);
        }
    }
}
