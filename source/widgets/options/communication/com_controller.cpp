#include <QComboBox>

#include "com_model.h"
#include "com_controller.h"

void ComController::on_View_Initialized(ElementManager* manager) {
    
    // Does nothing...
}

void ComController::on_View_Changed() {
    
    // Does nothing...
}

void ComController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == ComModel::FIELD_MODE) {
        
        QComboBox* mode = (QComboBox*)manager
            ->get(ComModel::FIELD_MODE);
        
        for (int i = 0; i < mode->count(); i++) {
            if (mode->itemText(i) == value) {
                mode->setCurrentIndex(i); break;
            }
        }
    }
    else if (key == ComModel::FIELD_PORT) {
        
        QComboBox* port = (QComboBox*)manager
            ->get(ComModel::FIELD_PORT);
        
        for (int i = 0; i < port->count(); i++) {
            if (port->itemText(i) == value) {
                port->setCurrentIndex(i); break;
            }
        }
    }
}

void ComController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QComboBox* mode = (QComboBox*)manager
        ->get(ComModel::FIELD_MODE);
    
    QComboBox* port = (QComboBox*)manager
        ->get(ComModel::FIELD_PORT);
    
    mode->setCurrentText(0);
    
    if (mode->count()) {
        port->setCurrentIndex(0);
    }
}
