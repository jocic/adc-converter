#include <QComboBox>

#include "ser_model.h"
#include "ser_controller.h"

void SerController::on_View_Initialized(ElementManager* manager) {
    
    this->set_ElementManager(manager);
}

void SerController::on_View_Changed() {
    
    // Does nothing...
}

void SerController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == SerModel::FIELD_BAUD_RATE) {
        
        QComboBox* cmb_baud = (QComboBox*)manager
            ->get(SerModel::FIELD_BAUD_RATE);
        
        for (int i = 0; i < cmb_baud->count(); i++) {
            if (cmb_baud->itemText(i) == value) {
                cmb_baud->setCurrentIndex(i); break;
            }
        }
    }
    else if (key == SerModel::FIELD_DATA_BITS) {
        
        QComboBox* cmb_data = (QComboBox*)manager
            ->get(SerModel::FIELD_DATA_BITS);
        
        for (int i = 0; i < cmb_data->count(); i++) {
            if (cmb_data->itemText(i) == value) {
                cmb_data->setCurrentIndex(i); break;
            }
        }
    }
    else if (key == SerModel::FIELD_PARITY_BITS) {
        
        QComboBox* cmb_parity = (QComboBox*)manager
            ->get(SerModel::FIELD_PARITY_BITS);
        
        for (int i = 0; i < cmb_parity->count(); i++) {
            if (cmb_parity->itemText(i) == value) {
                cmb_parity->setCurrentIndex(i); break;
            }
        }
    }
    else if (key == SerModel::FIELD_STOP_BITS) {
        
        QComboBox* cmb_stop = (QComboBox*)manager
            ->get(SerModel::FIELD_STOP_BITS);
        
        for (int i = 0; i < cmb_stop->count(); i++) {
            if (cmb_stop->itemText(i) == value) {
                cmb_stop->setCurrentIndex(i); break;
            }
        }
    }
    else if (key == SerModel::FIELD_FLOW_CONTROL) {
        
        QComboBox* cmb_flow = (QComboBox*)manager
            ->get(SerModel::FIELD_FLOW_CONTROL);
        
        for (int i = 0; i < cmb_flow->count(); i++) {
            if (cmb_flow->itemText(i) == value) {
                cmb_flow->setCurrentIndex(i); break;
            }
        }
    }
}

void SerController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QComboBox* cmb_baud = (QComboBox*)manager
        ->get(SerModel::FIELD_DATA_BITS);
    
    for (int i = 0; i < cmb_baud->count(); i++) {
        if (cmb_baud->itemText(i) == "19200") {
            cmb_baud->setCurrentIndex(i); break;
        }
    }
    
    QComboBox* cmb_data = (QComboBox*)manager
        ->get(SerModel::FIELD_DATA_BITS);
    
    for (int i = 0; i < cmb_data->count(); i++) {
        if (cmb_data->itemText(i) == "8") {
            cmb_data->setCurrentIndex(i); break;
        }
    }
    
    QComboBox* cmb_parity = (QComboBox*)manager
        ->get(SerModel::FIELD_PARITY_BITS);
    
    for (int i = 0; i < cmb_parity->count(); i++) {
        if (cmb_parity->itemText(i) == "None") {
            cmb_parity->setCurrentIndex(i); break;
        }
    }
    
    QComboBox* cmb_stop = (QComboBox*)manager
        ->get(SerModel::FIELD_STOP_BITS);
    
    for (int i = 0; i < cmb_stop->count(); i++) {
        if (cmb_stop->itemText(i) == "1/1") {
            cmb_stop->setCurrentIndex(i); break;
        }
    }
    
    QComboBox* cmb_flow = (QComboBox*)manager
        ->get(SerModel::FIELD_FLOW_CONTROL);
    
    for (int i = 0; i < cmb_flow->count(); i++) {
        if (cmb_flow->itemText(i) == "None") {
            cmb_flow->setCurrentIndex(i); break;
        }
    }
}
