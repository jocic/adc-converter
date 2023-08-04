#include <QLabel>

#include "gen_model.h"
#include "gen_controller.h"

void GenController::on_View_Initialized(ElementManager* manager) {
    
    this->set_ElementManager(manager);
}

void GenController::on_View_Changed() {
    
    // Does nothing...
}

void GenController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == GenModel::FIELD_SAMPLES) {
        
        QLabel* samples = (QLabel*)manager
            ->get(GenModel::FIELD_SAMPLES);
        
        samples->setText(value);
    }
    else if (key == GenModel::FIELD_DURATION) {
        
        QLabel* port = (QLabel*)manager
            ->get(GenModel::FIELD_DURATION);
        
        port->setText(value);
    }
}

void GenController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QLabel* samples = (QLabel*)manager
        ->get(GenModel::FIELD_SAMPLES);
    
    QLabel* duration = (QLabel*)manager
        ->get(GenModel::FIELD_DURATION);
    
    samples->setText("N/D");
    duration->setText("N/D");
}
