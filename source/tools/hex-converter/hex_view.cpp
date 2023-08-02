#include <QDebug>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>

#include "mvc/element_manager.h"
#include "hex_model.h"
#include "hex_view.h"

void HexView::initialize(QWidget* parent) {
    
    // Arrange View
    
    QGroupBox*   box       = new QGroupBox();
    QFormLayout* layout    = new QFormLayout();
    QLabel*      hex_label = new QLabel();
    QLineEdit*   hex_text  = new QLineEdit();
    QLabel*      dec_label = new QLabel();
    QLineEdit*   dec_text  = new QLineEdit();
    
    box->setLayout(layout);
    box->setTitle("Hexadecimal Converter");
    
    hex_label->setText("HEX");
    layout->addRow(hex_label, hex_text);
    
    dec_label->setText("DEC");
    layout->addRow(dec_label, dec_text);
    
    parent->layout()->addWidget(box);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push(HexModel::FIELD_DECIMAL, dec_text);
    manager->push(HexModel::FIELD_HEXADECIMAL, hex_text);
    
    emit HexView::sig_View_Initialized(manager);
}
