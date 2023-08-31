#include <QDebug>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>

#include "app/mvc/element_manager.h"
#include "stream_model.h"
#include "stream_view.h"

void StreamView::initialize(QWidget* parent) {
    
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
    cmb_bps->addItems({ "8", "16", "32" });
    cmb_bps->setCurrentIndex(1);
    layout->addRow(lbl_bps, cmb_bps);
    
    cb_sign->setText("Signed Samples");
    cb_sign->setChecked(true);
    layout->addRow(cb_sign);
    
    parent->layout()->addWidget(box);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push(StreamModel::FIELD_SAMPLE_RATE, txt_rate);
    manager->push(StreamModel::FIELD_BITS_PER_SAMPLE, cmb_bps);
    manager->push(StreamModel::FIELD_SIGNED, cb_sign);
    
    emit StreamView::sig_View_Initialized(manager);
}
