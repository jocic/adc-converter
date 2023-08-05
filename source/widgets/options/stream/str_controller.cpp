#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>

#include "str_model.h"
#include "str_controller.h"

void StrController::on_View_Initialized(ElementManager* manager) {
    
    // Does nothing...
}

void StrController::on_View_Changed() {
    
    // Does nothing...
}

void StrController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == StrModel::FIELD_SAMPLE_RATE) {
        
        QLineEdit* sample_rate = (QLineEdit*)manager
            ->get(StrModel::FIELD_SAMPLE_RATE);
        
        sample_rate->setText(value);
    }
    else if (key == StrModel::FIELD_BITS_PER_SAMPLE) {
        
        QComboBox* bits_per_sample = (QComboBox*)manager
            ->get(StrModel::FIELD_BITS_PER_SAMPLE);
        
        for (quint8 i = 0; i < bits_per_sample->count(); i++) {
            
            if (bits_per_sample->itemText(i) == value) {
                bits_per_sample->setCurrentIndex(i); break;
            }
        }
    }
    else if (key == StrModel::FIELD_SIGNED) {
        
        QCheckBox* sample_signed = (QCheckBox*)manager
            ->get(StrModel::FIELD_SIGNED);
        
        sample_signed->setChecked(value == "true");
    }
}

void StrController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QLineEdit* sample_rate = (QLineEdit*)manager
        ->get(StrModel::FIELD_SAMPLE_RATE);
    
    QComboBox* bits_per_sample = (QComboBox*)manager
        ->get(StrModel::FIELD_BITS_PER_SAMPLE);
    
    QCheckBox* sample_signed = (QCheckBox*)manager
        ->get(StrModel::FIELD_SIGNED);
    
    sample_rate->setText("44100");
    
    bits_per_sample->setCurrentIndex(0);
    
    sample_signed->setChecked(false);
}
