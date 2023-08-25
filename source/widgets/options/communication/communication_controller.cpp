#include <QSerialPortInfo>
#include <QComboBox>

#include "communication_model.h"
#include "communication_controller.h"

void CommunicationController::on_View_Initialized(ElementManager* manager) {
    
    this->registerField(CommunicationModel::FIELD_MODE,
        QComboBox::staticMetaObject.className());
    
    this->registerField(CommunicationModel::FIELD_PORT,
        QComboBox::staticMetaObject.className());
    
    this->on_RefreshPorts();
}

void CommunicationController::on_View_Changed() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QComboBox* port = (QComboBox*)manager
        ->get(CommunicationModel::FIELD_PORT);
    
    QComboBox* mode = (QComboBox*)manager
        ->get(CommunicationModel::FIELD_MODE);
    
    emit CommunicationController::sig_Mediator_Notify("com_data", {
        { "port", port->currentText() }, 
        { "mode", mode->currentText() }
    });
}

void CommunicationController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == CommunicationModel::FIELD_MODE) {
        
        QComboBox* mode = (QComboBox*)manager
            ->get(CommunicationModel::FIELD_MODE);
        
        for (int i = 0; i < mode->count(); i++) {
            if (mode->itemText(i) == value) {
                mode->setCurrentIndex(i); break;
            }
        }
    }
    else if (key == CommunicationModel::FIELD_PORT) {
        
        QComboBox* port = (QComboBox*)manager
            ->get(CommunicationModel::FIELD_PORT);
        
        for (int i = 0; i < port->count(); i++) {
            if (port->itemText(i) == value) {
                port->setCurrentIndex(i); break;
            }
        }
    }
}

void CommunicationController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QComboBox* mode = (QComboBox*)manager
        ->get(CommunicationModel::FIELD_MODE);
    
    QComboBox* port = (QComboBox*)manager
        ->get(CommunicationModel::FIELD_PORT);
    
    mode->setCurrentText(0);
    
    if (mode->count()) {
        port->setCurrentIndex(0);
    }
}

void CommunicationController::on_Mediator_Notify(QString topic,
    QMap<QString,QString> params) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QComboBox* mode = (QComboBox*)manager
        ->get(CommunicationModel::FIELD_MODE);
    
    QComboBox* port = (QComboBox*)manager
        ->get(CommunicationModel::FIELD_PORT);
    
    if (topic == "stream_started") {
        mode->setEnabled(false);
        port->setEnabled(false);
    }
    else if (topic == "stream_ended") {
        mode->setEnabled(true);
        port->setEnabled(true);
    }
    else if (topic == "refresh_ports") {
        this->on_RefreshPorts();
    }
}

void CommunicationController::on_RefreshPorts() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QComboBox* mode = (QComboBox*)manager
        ->get(CommunicationModel::FIELD_MODE);
    
    QComboBox* port = (QComboBox*)manager
        ->get(CommunicationModel::FIELD_PORT);
    
    quint8 rate_index;
    quint8 rate_temp;
    
    qDebug() << "Enumerating COM ports...";
    
    // COM Ports
    
    port->clear();
    
    for (const auto& serial_port : QSerialPortInfo::availablePorts()) {
        port->addItem(serial_port.portName());
        qDebug() << "Found:" << serial_port.portName();
    }
}
