#include <QDebug>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>

#include "mvc/element_manager.h"
#include "smp_model.h"
#include "smp_view.h"

void SmpView::initialize(QWidget* parent) {
    
    // Arrange View
    
    QGroupBox*   box      = new QGroupBox();
    QFormLayout* layout   = new QFormLayout();
    QLabel*      lbl_rate = new QLabel();
    QLineEdit*   txt_rate = new QLineEdit();
    QLabel*      lbl_bps  = new QLabel();
    QComboBox*   cmb_bps  = new QComboBox();
    QCheckBox*   cb_sign  = new QCheckBox();
    
    box->setLayout(layout);
    box->setTitle("Samples");
    
    lbl_rate->setText("Sample Rate");
    txt_rate->setText("44100");
    layout->addRow(lbl_rate, txt_rate);
    
    lbl_bps->setText("Bits Per Sample");
    cmb_bps->addItems({ "8", "16", "24", "32" });
    layout->addRow(lbl_bps, cmb_bps);
    
    cb_sign->setText("Signed Samples");
    layout->addRow(cb_sign);
    
    parent->layout()->addWidget(box);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push(SmpModel::FIELD_SAMPLE_RATE, txt_rate);
    manager->push(SmpModel::FIELD_BITS_PER_SAMPLE, cmb_bps);
    manager->push(SmpModel::FIELD_SIGNED, cb_sign);
    
    emit SmpView::sig_View_Initialized(manager);
}
