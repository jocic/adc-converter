#include <QLineEdit>

#include "app/converters/decimal_converter.h"
#include "decimal_model.h"
#include "decimal_controller.h"

void DecimalController::on_View_Initialized(ElementManager* manager) {
    
    this->tuneTo("stream_started");
    this->tuneTo("stream_ended");
    
    //////////////////////////////
    
    QLineEdit* txt_dec = (QLineEdit*)manager
        ->get(DecimalModel::FIELD_DECIMAL);
    
    connect(txt_dec, &QLineEdit::textChanged,
        this, &DecimalController::on_View_Changed);
}

void DecimalController::on_View_Changed() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    DecimalModel*       model   = (DecimalModel*)this->get_Model();
    
    DecimalConverter* converter = new DecimalConverter();
    
    QLineEdit* txt_dec = (QLineEdit*)manager
        ->get(DecimalModel::FIELD_DECIMAL);
    
    QString input = txt_dec->text();
    
    converter->set_ConversionType(DecimalConverter::Type::HEX);
    
    if (input.startsWith('-')) {
        converter->set_Signed(true);
    }
    
    QString output = converter->convert(input);
    
    model->set_Hexadecimal(output);
}

void DecimalController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == DecimalModel::FIELD_DECIMAL) {
        
        QLineEdit* decimal = (QLineEdit*)manager
            ->get(DecimalModel::FIELD_DECIMAL);
        
        decimal->setText(value);
    }
    else if (key == DecimalModel::FIELD_HEXADECIMAL) {
        
        QLineEdit* hexadecimal = (QLineEdit*)manager
            ->get(DecimalModel::FIELD_HEXADECIMAL);
        
        hexadecimal->setText(value);
    }
}

void DecimalController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QLineEdit* decimal = (QLineEdit*)manager
        ->get(DecimalModel::FIELD_DECIMAL);
    
    QLineEdit* hexadecimal = (QLineEdit*)manager
        ->get(DecimalModel::FIELD_HEXADECIMAL);
    
    decimal->setText("");
    hexadecimal->setText("");
}

void DecimalController::on_Broadcast(QString topic,
    QMap<QString,QString> params) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QLineEdit* decimal = (QLineEdit*)manager
        ->get(DecimalModel::FIELD_DECIMAL);
    
    QLineEdit* hexadecimal = (QLineEdit*)manager
        ->get(DecimalModel::FIELD_HEXADECIMAL);
    
    if (topic == "stream_started") {
        hexadecimal->setEnabled(false);
        decimal->setEnabled(false);
    }
    else if (topic == "stream_ended") {
        hexadecimal->setEnabled(true);
        decimal->setEnabled(true);
    }
}

void DecimalController::on_Broadcast_ALT(QString topic, void* params) {
    
    // Does nothing...
}
