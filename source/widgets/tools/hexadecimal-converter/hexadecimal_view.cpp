#include <QDebug>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>

#include "app/mvc/element_manager.h"
#include "hexadecimal_model.h"
#include "hexadecimal_view.h"

void HexadecimalView::initialize(QWidget* parent) {
    
    // Arrange View
    
    QGroupBox*   box        = new QGroupBox();
    QFormLayout* layout     = new QFormLayout();
    QLabel*      hex_label  = new QLabel();
    QLineEdit*   hex_text   = new QLineEdit();
    QLabel*      dec_label  = new QLabel();
    QLineEdit*   dec_text   = new QLineEdit();
    QCheckBox*   val_signed = new QCheckBox();
    
    box->setLayout(layout);
    box->setTitle("Hexadecimal Converter");
    
    hex_label->setText("HEX");
    layout->addRow(hex_label, hex_text);
    
    dec_label->setText("DEC");
    layout->addRow(dec_label, dec_text);
    
    val_signed->setText("Signed");
    layout->addRow(val_signed);
    
    parent->layout()->addWidget(box);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push(HexadecimalModel::FIELD_DECIMAL, dec_text);
    manager->push(HexadecimalModel::FIELD_HEXADECIMAL, hex_text);
    manager->push(HexadecimalModel::FIELD_SIGNED, val_signed);
    
    emit HexadecimalView::sig_View_Initialized(manager);
}
