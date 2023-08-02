#include <QLineEdit>

#include "hex_model.h"
#include "hex_controller.h"

void HexController::on_View_Initialized(ElementManager* manager) {
    
    this->set_ElementManager(manager);
}

void HexController::on_View_Changed() {
    
    // Does nothing...
}

void HexController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == HexModel::FIELD_HEXADECIMAL) {
        
        QLineEdit* hexadecimal = (QLineEdit*)manager
            ->get(HexModel::FIELD_HEXADECIMAL);
        
        hexadecimal->setText(value);
    }
    else if (key == HexModel::FIELD_DECIMAL) {
        
        QLineEdit* decimal = (QLineEdit*)manager
            ->get(HexModel::FIELD_DECIMAL);
        
        decimal->setText(value);
    }
}

void HexController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QLineEdit* hexadecimal = (QLineEdit*)manager
        ->get(HexModel::FIELD_HEXADECIMAL);
    
    QLineEdit* decimal = (QLineEdit*)manager
        ->get(HexModel::FIELD_DECIMAL);
    
    hexadecimal->setText("");
    decimal->setText("");
}
