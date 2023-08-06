#include <QComboBox>

#include "serial_model.h"
#include "serial_controller.h"

void SerialController::on_View_Initialized(ElementManager* manager) {
    
    // Does nothing...
}

void SerialController::on_View_Changed() {
    
    // Does nothing...
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
        ->get(SerialModel::FIELD_DATA_BITS);
    
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
