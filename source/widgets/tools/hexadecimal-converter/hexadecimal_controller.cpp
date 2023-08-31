#include <QDebug>
#include <QLineEdit>
#include <QCheckBox>

#include "app/app_mediator.h"
#include "app/converters/hexadecimal_converter.h"
#include "hexadecimal_model.h"
#include "hexadecimal_controller.h"

void HexadecimalController::on_View_Initialized(ElementManager* manager) {
    
    this->tuneTo(AppMediator::Channel::APP_EVENTS);
    this->tuneTo(AppMediator::Channel::STREAM_EVENTS);
    
    //////////////////////////////
    
    QLineEdit* txt_hex = (QLineEdit*)manager
        ->get(HexadecimalModel::FIELD_HEXADECIMAL);
    QCheckBox* cb_sig = (QCheckBox*)manager
        ->get(HexadecimalModel::FIELD_SIGNED);
    
    connect(txt_hex, &QLineEdit::textChanged,
        this, &HexadecimalController::on_View_Changed);
    
    connect(cb_sig, &QCheckBox::stateChanged,
        this, &HexadecimalController::on_View_Changed);
}

void HexadecimalController::on_View_Changed() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    HexadecimalModel*       model   = (HexadecimalModel*)this->get_Model();
    
    HexadecimalConverter* converter = new HexadecimalConverter();
    
    QLineEdit* txt_hex = (QLineEdit*)manager
        ->get(HexadecimalModel::FIELD_HEXADECIMAL);
    QCheckBox* cb_sig = (QCheckBox*)manager
        ->get(HexadecimalModel::FIELD_SIGNED);
    
    QString input  = txt_hex->text();
    bool    is_sig = cb_sig->isChecked();
    
    converter->set_ConversionType(HexadecimalConverter::Type::DEC);
    converter->set_Signed(is_sig);
    
    QString output = converter->convert(input);
    
    model->set_Decimal(output);
}

void HexadecimalController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == HexadecimalModel::FIELD_HEXADECIMAL) {
        
        QLineEdit* hexadecimal = (QLineEdit*)manager
            ->get(HexadecimalModel::FIELD_HEXADECIMAL);
        
        hexadecimal->setText(value);
    }
    else if (key == HexadecimalModel::FIELD_DECIMAL) {
        
        QLineEdit* decimal = (QLineEdit*)manager
            ->get(HexadecimalModel::FIELD_DECIMAL);
        
        decimal->setText(value);
    }
    else if (key == HexadecimalModel::FIELD_SIGNED) {
        
        QCheckBox* val_signed = (QCheckBox*)manager
            ->get(HexadecimalModel::FIELD_SIGNED);
        
        val_signed->setChecked(value == "true");
    }
}

void HexadecimalController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QLineEdit* hexadecimal = (QLineEdit*)manager
        ->get(HexadecimalModel::FIELD_HEXADECIMAL);
    
    QLineEdit* decimal = (QLineEdit*)manager
        ->get(HexadecimalModel::FIELD_DECIMAL);
    
    QCheckBox* val_signed = (QCheckBox*)manager
        ->get(HexadecimalModel::FIELD_SIGNED);
    
    hexadecimal->setText("");
    decimal->setText("");
    val_signed->setChecked(false);
}

void HexadecimalController::on_Broadcast(quint64 ch, app_data_t data) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QLineEdit* hexadecimal = (QLineEdit*)manager
        ->get(HexadecimalModel::FIELD_HEXADECIMAL);
    
    QLineEdit* decimal = (QLineEdit*)manager
        ->get(HexadecimalModel::FIELD_DECIMAL);
    
    QCheckBox* val_signed = (QCheckBox*)manager
        ->get(HexadecimalModel::FIELD_SIGNED);
    
    // App Events
    
    if (ch == AppMediator::Channel::APP_EVENTS) {
        
        if (data.event == "hex_selected") {
            
            QLineEdit* hexadecimal = (QLineEdit*)manager
                ->get(HexadecimalModel::FIELD_HEXADECIMAL);
            
            hexadecimal->setText(data.str_value);
        }
    }
    
    // Stream Events
    
    else if (ch == AppMediator::Channel::STREAM_EVENTS) {
        
        if (data.event == "stream_started") {
            hexadecimal->setEnabled(false);
            decimal->setEnabled(false);
            val_signed->setEnabled(false);
        }
        else if (data.event == "stream_ended") {
            hexadecimal->setEnabled(true);
            decimal->setEnabled(true);
            val_signed->setEnabled(true);
        }
    }
}
