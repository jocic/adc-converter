#include <QDebug>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>

#include "mvc/element_manager.h"
#include "decimal_model.h"
#include "decimal_view.h"

void DecimalView::initialize(QWidget* parent) {
    
    // Arrange View
    
    QGroupBox*   box       = new QGroupBox();
    QFormLayout* layout    = new QFormLayout();
    QLabel*      dec_label = new QLabel();
    QLineEdit*   dec_text  = new QLineEdit();
    QLabel*      hex_label = new QLabel();
    QLineEdit*   hex_text  = new QLineEdit();
    
    box->setLayout(layout);
    box->setTitle("Decimal Converter");
    
    dec_label->setText("DEC");
    layout->addRow(dec_label, dec_text);
    
    hex_label->setText("HEX");
    layout->addRow(hex_label, hex_text);
    
    parent->layout()->addWidget(box);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push(DecimalModel::FIELD_DECIMAL, dec_text);
    manager->push(DecimalModel::FIELD_HEXADECIMAL, hex_text);
    
    emit DecimalView::sig_View_Initialized(manager);
}
