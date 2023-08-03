#include <QDebug>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLineEdit>

#include "mvc/element_manager.h"
#include "sr_model.h"
#include "sr_view.h"

void SrView::initialize(QWidget* parent) {
    
    // Arrange View
    
    QGroupBox*   box    = new QGroupBox();
    QFormLayout* layout = new QFormLayout();
    QLineEdit*   rate   = new QLineEdit();
    
    box->setLayout(layout);
    box->setTitle("Sample Rate");
    
    rate->setText("44100");
    
    layout->addRow(rate);
    
    parent->layout()->addWidget(box);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push(SrModel::FIELD_SAMPLE_RATE, rate);
    
    emit SrView::sig_View_Initialized(manager);
}
