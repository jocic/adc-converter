#include <QLineEdit>

#include "dec_model.h"
#include "dec_controller.h"

void DecController::on_View_Initialized(ElementManager* manager) {
    
    this->set_ElementManager(manager);
}

void DecController::on_View_Changed() {
    
    // Does nothing...
}

void DecController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == DecModel::FIELD_DECIMAL) {
        
        QLineEdit* decimal = (QLineEdit*)manager
            ->get(DecModel::FIELD_DECIMAL);
        
        decimal->setText(value);
    }
    else if (key == DecModel::FIELD_HEXADECIMAL) {
        
        QLineEdit* hexadecimal = (QLineEdit*)manager
            ->get(DecModel::FIELD_HEXADECIMAL);
        
        hexadecimal->setText(value);
    }
}

void DecController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QLineEdit* decimal = (QLineEdit*)manager
        ->get(DecModel::FIELD_DECIMAL);
    
    QLineEdit* hexadecimal = (QLineEdit*)manager
        ->get(DecModel::FIELD_HEXADECIMAL);
    
    decimal->setText("");
    hexadecimal->setText("");
}
