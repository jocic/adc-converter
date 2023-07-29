#include <QDebug>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLineEdit>>

#include "mvc/element_manager.h"
#include "sr_view.h"

void SrView::initialize(QWidget* parent) {
    
    // Arrange View
    
    QGroupBox*   box     = new QGroupBox();
    QFormLayout* layout  = new QFormLayout();
    QLineEdit*   samples = new QLineEdit();
    
    box->setLayout(layout);
    box->setTitle("Sample Rate");
    
    samples->setText("44100");
    
    layout->addRow(samples);
    
    parent->layout()->addWidget(box);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    //manager->push(BpsModel::FIELD_BITS_PER_SAMPLE, combo);
    //manager->push(BpsModel::FIELD_SIGNED, check);
    
    emit SrView::sig_View_Initialized(manager);
}
