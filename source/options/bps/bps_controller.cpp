#include <QComboBox>
#include <QCheckBox>

#include "bps_model.h"
#include "bps_controller.h"

void BpsController::on_View_Initialized(ElementManager* manager) {
    
    this->set_ElementManager(manager);
}

void BpsController::on_View_Changed() {
    
    // Does nothing...
}

void BpsController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == BpsModel::FIELD_BITS_PER_SAMPLE) {
        
        QComboBox* bits_per_sample = (QComboBox*)manager
            ->get(BpsModel::FIELD_BITS_PER_SAMPLE);
        
        for (quint8 i = 0; i < bits_per_sample->count(); i++) {
            
            if (bits_per_sample->itemText(i) == value) {
                bits_per_sample->setCurrentIndex(i); break;
            }
        }
    }
    else if (key == BpsModel::FIELD_SIGNED) {
        
        QCheckBox* sample_signed = (QCheckBox*)manager
            ->get(BpsModel::FIELD_SIGNED);
        
        sample_signed->setChecked(value == "true");
    }
}

void BpsController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QComboBox* bits_per_sample = (QComboBox*)manager
        ->get(BpsModel::FIELD_BITS_PER_SAMPLE);
    
    QCheckBox* sample_signed = (QCheckBox*)manager
        ->get(BpsModel::FIELD_SIGNED);
    
    bits_per_sample->setCurrentIndex(0);
    
    sample_signed->setChecked(false);
}
