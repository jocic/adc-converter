#include <QLineEdit>

#include "reference_model.h"
#include "reference_controller.h"

void ReferenceController::on_View_Initialized(ElementManager* manager) {
    
    this->tuneTo("stream_started");
    this->tuneTo("stream_ended");
    this->tuneTo("stream_params");
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

void ReferenceController::on_Broadcast(QString topic,
    QMap<QString,QString> params) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    ReferenceModel* model = (ReferenceModel*)this->get_Model();
    
    QLineEdit* positive = (QLineEdit*)manager
        ->get(ReferenceModel::FIELD_POSITIVE);
    
    QLineEdit* negative = (QLineEdit*)manager
        ->get(ReferenceModel::FIELD_NEGATIVE);
    
    if (topic == "stream_started") {
        positive->setEnabled(false);
        negative->setEnabled(false);
    }
    else if (topic == "stream_ended") {
        positive->setEnabled(true);
        negative->setEnabled(true);
    }
    else if (topic == "stream_params") {
        
        if (params.contains("positive_reference")) {
            model->set_Positive(params["positive_reference"]);
        }
        
        if (params.contains("negative_reference")) {
            model->set_Negative(params["negative_reference"]);
        }
    }
}
