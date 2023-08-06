#include <QLabel>

#include "general_model.h"
#include "general_controller.h"

void GeneralController::on_View_Initialized(ElementManager* manager) {
    
    // Does nothing...
}

void GeneralController::on_View_Changed() {
    
    // Does nothing...
}

void GeneralController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == GeneralModel::FIELD_SAMPLES) {
        
        QLabel* samples = (QLabel*)manager
            ->get(GeneralModel::FIELD_SAMPLES);
        
        samples->setText(value);
    }
    else if (key == GeneralModel::FIELD_DURATION) {
        
        QLabel* port = (QLabel*)manager
            ->get(GeneralModel::FIELD_DURATION);
        
        port->setText(value);
    }
}

void GeneralController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QLabel* samples = (QLabel*)manager
        ->get(GeneralModel::FIELD_SAMPLES);
    
    QLabel* duration = (QLabel*)manager
        ->get(GeneralModel::FIELD_DURATION);
    
    samples->setText("N/D");
    duration->setText("N/D");
}
