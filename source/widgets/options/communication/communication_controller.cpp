#include <QComboBox>

#include "communication_model.h"
#include "communication_controller.h"

void CommunicationController::on_View_Initialized(ElementManager* manager) {
    
    // Does nothing...
}

void CommunicationController::on_View_Changed() {
    
    // Does nothing...
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
    
    // Does nothing...
}
