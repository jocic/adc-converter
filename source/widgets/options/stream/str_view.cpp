#include <QDebug>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>

#include "mvc/element_manager.h"
#include "str_model.h"
#include "str_view.h"

void StrView::initialize(QWidget* parent) {
    
    // Arrange View
    
    QGroupBox*   box      = new QGroupBox();
    QFormLayout* layout   = new QFormLayout();
    QLabel*      lbl_rate = new QLabel();
    QLineEdit*   txt_rate = new QLineEdit();
    QLabel*      lbl_bps  = new QLabel();
    QComboBox*   cmb_bps  = new QComboBox();
    QCheckBox*   cb_sign  = new QCheckBox();
    
    box->setLayout(layout);
    box->setTitle("Stream");
    
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
    
    manager->push(StrModel::FIELD_SAMPLE_RATE, txt_rate);
    manager->push(StrModel::FIELD_BITS_PER_SAMPLE, cmb_bps);
    manager->push(StrModel::FIELD_SIGNED, cb_sign);
    
    emit StrView::sig_View_Initialized(manager);
}
