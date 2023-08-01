#include <QDebug>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>

#include "mvc/element_manager.h"
#include "ref_model.h"
#include "ref_view.h"

void RefView::initialize(QWidget* parent) {
    
    // Arrange View
    
    QGroupBox*   box       = new QGroupBox();
    QFormLayout* layout    = new QFormLayout();
    QLabel*      pos_label = new QLabel();
    QLineEdit*   pos_text  = new QLineEdit();
    QLabel*      neg_label = new QLabel();
    QLineEdit*   neg_text  = new QLineEdit();
    
    box->setLayout(layout);
    box->setTitle("Reference");
    
    pos_label->setText("Positive");
    pos_text->setText("5000");
    layout->addRow(pos_label, pos_text);
    
    neg_label->setText("Negative");
    neg_text->setText("0");
    layout->addRow(neg_label, neg_text);
    
    parent->layout()->addWidget(box);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push(RefModel::FIELD_POSITIVE, pos_text);
    manager->push(RefModel::FIELD_NEGATIVE, neg_text);
    
    emit RefView::sig_View_Initialized(manager);
}
