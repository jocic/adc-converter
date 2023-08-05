#include <QLineEdit>

#include "converters/dec_converter.h"
#include "dec_model.h"
#include "dec_controller.h"

void DecController::on_View_Initialized(ElementManager* manager) {
    
    QLineEdit* txt_dec = (QLineEdit*)manager
        ->get(DecModel::FIELD_DECIMAL);
    
    connect(txt_dec, &QLineEdit::textChanged,
        this, &DecController::on_View_Changed);
}

void DecController::on_View_Changed() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    DecModel*       model   = (DecModel*)this->get_Model();
    
    DecConverter* converter = new DecConverter();
    
    QLineEdit* txt_dec = (QLineEdit*)manager
        ->get(DecModel::FIELD_DECIMAL);
    
    QString input = txt_dec->text();
    
    converter->set_ConversionType(DecConverter::Type::HEX);
    
    if (input.startsWith('-')) {
        converter->set_Signed(true);
    }
    
    QString output = converter->convert(input);
    
    model->set_Hexadecimal(output);
}

void DecController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == DecModel::FIELD_DECIMAL) {
        
        QLineEdit* decimal = (QLineEdit*)manager
            ->get(DecModel::FIELD_DECIMAL);
        
        decimal->setText(value);
    }
    else if (key == DecModel::FIELD_HEXADECIMAL) {
        
        QLineEdit* hexadecimal = (QLineEdit*)manager
            ->get(DecModel::FIELD_HEXADECIMAL);
        
        hexadecimal->setText(value);
    }
}

void DecController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QLineEdit* decimal = (QLineEdit*)manager
        ->get(DecModel::FIELD_DECIMAL);
    
    QLineEdit* hexadecimal = (QLineEdit*)manager
        ->get(DecModel::FIELD_HEXADECIMAL);
    
    decimal->setText("");
    hexadecimal->setText("");
}
