#include <QLineEdit>

#include "ref_model.h"
#include "ref_controller.h"

void RefController::on_View_Initialized(ElementManager* manager) {
    
    this->set_ElementManager(manager);
}

void RefController::on_View_Changed() {
    
    // Does nothing...
}

void RefController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == RefModel::FIELD_POSITIVE) {
        
        QLineEdit* positive = (QLineEdit*)manager
            ->get(RefModel::FIELD_POSITIVE);
        
        positive->setText(value);
    }
    else if (key == RefModel::FIELD_NEGATIVE) {
        
        QLineEdit* negative = (QLineEdit*)manager
            ->get(RefModel::FIELD_NEGATIVE);
        
        negative->setText(value);
    }
}

void RefController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QLineEdit* positive = (QLineEdit*)manager
        ->get(RefModel::FIELD_POSITIVE);
    
    QLineEdit* negative = (QLineEdit*)manager
        ->get(RefModel::FIELD_NEGATIVE);
    
    positive->setText("5000");
    negative->setText("0");
}
