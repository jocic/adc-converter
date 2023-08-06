#include <QLineEdit>

#include "reference_model.h"
#include "reference_controller.h"

void ReferenceController::on_View_Initialized(ElementManager* manager) {
    
    // Does nothing...
}

void ReferenceController::on_View_Changed() {
    
    // Does nothing...
}

void ReferenceController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == ReferenceModel::FIELD_POSITIVE) {
        
        QLineEdit* positive = (QLineEdit*)manager
            ->get(ReferenceModel::FIELD_POSITIVE);
        
        positive->setText(value);
    }
    else if (key == ReferenceModel::FIELD_NEGATIVE) {
        
        QLineEdit* negative = (QLineEdit*)manager
            ->get(ReferenceModel::FIELD_NEGATIVE);
        
        negative->setText(value);
    }
}

void ReferenceController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QLineEdit* positive = (QLineEdit*)manager
        ->get(ReferenceModel::FIELD_POSITIVE);
    
    QLineEdit* negative = (QLineEdit*)manager
        ->get(ReferenceModel::FIELD_NEGATIVE);
    
    positive->setText("5000");
    negative->setText("0");
}