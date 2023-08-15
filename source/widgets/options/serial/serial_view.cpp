#include <QDebug>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>

#include "app/mvc/element_manager.h"
#include "serial_model.h"
#include "serial_view.h"

void SerialView::initialize(QWidget* parent) {
    
    // Arrange View
    
    QGroupBox*   box        = new QGroupBox();
    QFormLayout* layout     = new QFormLayout();
    QLabel*      lbl_baud   = new QLabel();
    QComboBox*   cmb_baud   = new QComboBox();
    QLabel*      lbl_data   = new QLabel();
    QComboBox*   cmb_data   = new QComboBox();
    QLabel*      lbl_stop   = new QLabel();
    QComboBox*   cmb_stop   = new QComboBox();
    QLabel*      lbl_parity = new QLabel();
    QComboBox*   cmb_parity = new QComboBox();
    QLabel*      lbl_flow   = new QLabel();
    QComboBox*   cmb_flow   = new QComboBox();
    
    box->setLayout(layout);
    box->setTitle("Serial");
    
    lbl_baud->setText("Baud Rate");
    cmb_baud->addItems({ "1200", "2400", "4800", "9600",
        "19200", "38400", "57600", "115200" });
    cmb_baud->setCurrentIndex(4);
    layout->addRow(lbl_baud, cmb_baud);
    
    lbl_data->setText("Data Bits");
    cmb_data->addItems({ "5", "6", "7", "8" });
    cmb_data->setCurrentIndex(3);
    layout->addRow(lbl_data, cmb_data);
    
    lbl_stop->setText("Stop Bits");
    cmb_stop->addItems({ "1/1", "1/2", "2/1" });
    cmb_stop->setCurrentIndex(0);
    layout->addRow(lbl_stop, cmb_stop);
    
    lbl_parity->setText("Parity Bit");
    cmb_parity->addItems({ "None", "Even", "Odd", "Space", "Mark" });
    cmb_parity->setCurrentIndex(0);
    layout->addRow(lbl_parity, cmb_parity);
    
    lbl_flow->setText("Flow Control");
    cmb_flow->addItems({ "None", "Hardware", "Software" });
    cmb_flow->setCurrentIndex(0);
    layout->addRow(lbl_flow, cmb_flow);
    
    parent->layout()->addWidget(box);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push(SerialModel::FIELD_BAUD_RATE, cmb_baud);    
    manager->push(SerialModel::FIELD_DATA_BITS, cmb_data);
    manager->push(SerialModel::FIELD_STOP_BITS, cmb_stop);  
    manager->push(SerialModel::FIELD_PARITY_BITS, cmb_parity);
    manager->push(SerialModel::FIELD_FLOW_CONTROL, cmb_flow);
    
    emit SerialView::sig_View_Initialized(manager);
}
