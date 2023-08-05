#include <QDebug>
#include <QLineEdit>
#include <QCheckBox>

#include "converters/hex_converter.h"
#include "hex_model.h"
#include "hex_controller.h"

void HexController::on_View_Initialized(ElementManager* manager) {
    
    QLineEdit* txt_hex = (QLineEdit*)manager
        ->get(HexModel::FIELD_HEXADECIMAL);
    QCheckBox* cb_sig = (QCheckBox*)manager
        ->get(HexModel::FIELD_SIGNED);
    
    connect(txt_hex, &QLineEdit::textChanged,
        this, &HexController::on_View_Changed);
    
    connect(cb_sig, &QCheckBox::stateChanged,
        this, &HexController::on_View_Changed);
}

void HexController::on_View_Changed() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    HexModel*       model   = (HexModel*)this->get_Model();
    
    HexConverter* converter = new HexConverter();
    
    QLineEdit* txt_hex = (QLineEdit*)manager
        ->get(HexModel::FIELD_HEXADECIMAL);
    QCheckBox* cb_sig = (QCheckBox*)manager
        ->get(HexModel::FIELD_SIGNED);
    
    QString input  = txt_hex->text();
    bool    is_sig = cb_sig->isChecked();
    
    converter->set_ConversionType(HexConverter::Type::DEC);
    converter->set_Signed(is_sig);
    
    QString output = converter->convert(input);
    
    model->set_Decimal(output);
}

void HexController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == HexModel::FIELD_HEXADECIMAL) {
        
        QLineEdit* hexadecimal = (QLineEdit*)manager
            ->get(HexModel::FIELD_HEXADECIMAL);
        
        hexadecimal->setText(value);
    }
    else if (key == HexModel::FIELD_DECIMAL) {
        
        QLineEdit* decimal = (QLineEdit*)manager
            ->get(HexModel::FIELD_DECIMAL);
        
        decimal->setText(value);
    }
    else if (key == HexModel::FIELD_SIGNED) {
        
        QCheckBox* val_signed = (QCheckBox*)manager
            ->get(HexModel::FIELD_SIGNED);
        
        val_signed->setChecked(value == "true");
    }
}

void HexController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QLineEdit* hexadecimal = (QLineEdit*)manager
        ->get(HexModel::FIELD_HEXADECIMAL);
    
    QLineEdit* decimal = (QLineEdit*)manager
        ->get(HexModel::FIELD_DECIMAL);
    
    QCheckBox* val_signed = (QCheckBox*)manager
        ->get(HexModel::FIELD_SIGNED);
    
    hexadecimal->setText("");
    decimal->setText("");
    val_signed->setChecked(false);
}
