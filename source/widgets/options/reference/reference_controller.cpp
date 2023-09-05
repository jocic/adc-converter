#include <QLineEdit>
#include <QCheckBox>

#include "app/app_mediator.h"
#include "reference_model.h"
#include "reference_controller.h"

void ReferenceController::on_View_Initialized(ElementManager* manager) {
    
    this->tuneTo(AppMediator::Channel::APP_EVENTS);
    this->tuneTo(AppMediator::Channel::STREAM_EVENTS);
    this->tuneTo(AppMediator::Channel::REFERENCE_PARAMS);
    
    this->registerField(ReferenceModel::FIELD_POSITIVE,
        QLineEdit::staticMetaObject.className());
    
    this->registerField(ReferenceModel::FIELD_NEGATIVE,
        QLineEdit::staticMetaObject.className());
    
    this->registerField(ReferenceModel::FIELD_CONVERT,
        QCheckBox::staticMetaObject.className());
}

void ReferenceController::on_View_Changed() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    // Fields
    
    QLineEdit* positive = (QLineEdit*)manager
        ->get(ReferenceModel::FIELD_POSITIVE);
    
    QLineEdit* negative = (QLineEdit*)manager
        ->get(ReferenceModel::FIELD_NEGATIVE);
    
    QCheckBox* convert = (QCheckBox*)manager
        ->get(ReferenceModel::FIELD_CONVERT);
    
    // Combile & Broadcast Data
    
    app_data_t data;
    
    data.ref_config.adc_positive   = positive->text().toLongLong();
    data.ref_config.adc_negative   = negative->text().toLongLong();
    data.ref_config.convert_values = convert->isChecked();
    
    emit ReferenceController::sig_Broadcast(
        AppMediator::Channel::REFERENCE_PARAMS, data);
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

void ReferenceController::on_Broadcast(quint64 ch, app_data_t data) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    ReferenceModel* model = (ReferenceModel*)this->get_Model();
    
    QLineEdit* positive = (QLineEdit*)manager
        ->get(ReferenceModel::FIELD_POSITIVE);
    
    QLineEdit* negative = (QLineEdit*)manager
        ->get(ReferenceModel::FIELD_NEGATIVE);
    
    // Stream Events
    
    if (ch == AppMediator::Channel::STREAM_EVENTS) {
        
        if (data.event == "stream_started") {
            positive->setEnabled(false);
            negative->setEnabled(false);
        }
        else if (data.event == "stream_ended") {
            positive->setEnabled(true);
            negative->setEnabled(true);
        }
    }
    
    // Reference Params
    
    else if (ch == AppMediator::Channel::REFERENCE_PARAMS) {
        
        if (data.event != "update") {
            return;
        }
        
        model->set_Positive(data.ref_config.adc_positive);
        model->set_Negative(data.ref_config.adc_negative);
    }
}
