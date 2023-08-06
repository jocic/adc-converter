#include <QDebug>
#include <QLineEdit>
#include <QCheckBox>

#include "converters/hexadecimal_converter.h"
#include "processing_model.h"
#include "processing_controller.h"

void ProcessingController::on_View_Initialized(ElementManager* manager) {
    
    QLineEdit* txt_hex = (QLineEdit*)manager
        ->get(ProcessingModel::FIELD_HEXADECIMAL);
    QCheckBox* cb_sig = (QCheckBox*)manager
        ->get(ProcessingModel::FIELD_SIGNED);
    
    connect(txt_hex, &QLineEdit::textChanged,
        this, &ProcessingController::on_View_Changed);
    
    connect(cb_sig, &QCheckBox::stateChanged,
        this, &ProcessingController::on_View_Changed);
}

void ProcessingController::on_View_Changed() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    ProcessingModel*       model   = (ProcessingModel*)this->get_Model();
    
    HexadecimalConverter* converter = new HexadecimalConverter();
    
    QLineEdit* txt_hex = (QLineEdit*)manager
        ->get(ProcessingModel::FIELD_HEXADECIMAL);
    QCheckBox* cb_sig = (QCheckBox*)manager
        ->get(ProcessingModel::FIELD_SIGNED);
    
    QString input  = txt_hex->text();
    bool    is_sig = cb_sig->isChecked();
    
    converter->set_ConversionType(HexadecimalConverter::Type::DEC);
    converter->set_Signed(is_sig);
    
    QString output = converter->convert(input);
    
    model->set_Decimal(output);
}

void ProcessingController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == ProcessingModel::FIELD_HEXADECIMAL) {
        
        QLineEdit* hexadecimal = (QLineEdit*)manager
            ->get(ProcessingModel::FIELD_HEXADECIMAL);
        
        hexadecimal->setText(value);
    }
    else if (key == ProcessingModel::FIELD_DECIMAL) {
        
        QLineEdit* decimal = (QLineEdit*)manager
            ->get(ProcessingModel::FIELD_DECIMAL);
        
        decimal->setText(value);
    }
    else if (key == ProcessingModel::FIELD_SIGNED) {
        
        QCheckBox* val_signed = (QCheckBox*)manager
            ->get(ProcessingModel::FIELD_SIGNED);
        
        val_signed->setChecked(value == "true");
    }
}

void ProcessingController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QLineEdit* hexadecimal = (QLineEdit*)manager
        ->get(ProcessingModel::FIELD_HEXADECIMAL);
    
    QLineEdit* decimal = (QLineEdit*)manager
        ->get(ProcessingModel::FIELD_DECIMAL);
    
    QCheckBox* val_signed = (QCheckBox*)manager
        ->get(ProcessingModel::FIELD_SIGNED);
    
    hexadecimal->setText("");
    decimal->setText("");
    val_signed->setChecked(false);
}
