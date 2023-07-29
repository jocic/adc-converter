#include <QLineEdit>

#include "sr_model.h"
#include "sr_controller.h"

void SrController::on_View_Initialized(ElementManager* manager) {
    
    this->set_ElementManager(manager);
}

void SrController::on_View_Changed() {
    
    // Does nothing...
}

void SrController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == SrModel::FIELD_SAMPLE_RATE) {
        
        QLineEdit* sample_rate = (QLineEdit*)manager
            ->get(SrModel::FIELD_SAMPLE_RATE);
        
        sample_rate->setText(value);
    }
}

void SrController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QLineEdit* sample_rate = (QLineEdit*)manager
        ->get(SrModel::FIELD_SAMPLE_RATE);
    
    sample_rate->setText("44100");
}
