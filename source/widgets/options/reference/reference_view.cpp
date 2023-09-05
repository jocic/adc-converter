#include <QDebug>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>

#include "app/mvc/element_manager.h"
#include "reference_model.h"
#include "reference_view.h"

void ReferenceView::initialize(QWidget* parent) {
    
    // Arrange View
    
    QGroupBox*   box       = new QGroupBox();
    QFormLayout* layout    = new QFormLayout();
    QLabel*      pos_label = new QLabel();
    QLineEdit*   pos_text  = new QLineEdit();
    QLabel*      neg_label = new QLabel();
    QLineEdit*   neg_text  = new QLineEdit();
    QCheckBox*   cb_conv   = new QCheckBox();
    
    box->setLayout(layout);
    box->setTitle("Reference");
    
    pos_label->setText("Positive");
    pos_text->setText("3300");
    layout->addRow(pos_label, pos_text);
    
    neg_label->setText("Negative");
    neg_text->setText("0");
    layout->addRow(neg_label, neg_text);
    
    cb_conv->setText("Convert Values");
    layout->addRow(cb_conv);
    
    parent->layout()->addWidget(box);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push(ReferenceModel::FIELD_POSITIVE, pos_text);
    manager->push(ReferenceModel::FIELD_NEGATIVE, neg_text);
    manager->push(ReferenceModel::FIELD_CONVERT, cb_conv);
    
    emit ReferenceView::sig_View_Initialized(manager);
}
