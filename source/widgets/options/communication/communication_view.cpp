#include <QDebug>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

#include "app/app_icons.h"
#include "app/mvc/element_manager.h"
#include "communication_model.h"
#include "communication_view.h"

void CommunicationView::initialize(QWidget* parent) {
    
    // Arrange View
    
    QGroupBox*   box      = new QGroupBox();
    QFormLayout* lay_root = new QFormLayout();
    QLabel*      lbl_port = new QLabel();
    QComboBox*   cmb_port = new QComboBox();
    QLabel*      lbl_mode = new QLabel();
    QComboBox*   cmb_mode = new QComboBox();
    
    box->setLayout(lay_root);
    box->setTitle("Communication");
    
    lbl_port->setText("Port");
    lay_root->addRow(lbl_port, cmb_port);
    
    lbl_mode->setText("Mode");
    cmb_mode->addItems({ "Text", "Binary" });
    lay_root->addRow(lbl_mode, cmb_mode);
    
    parent->layout()->addWidget(box);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push(CommunicationModel::FIELD_PORT, cmb_port);
    manager->push(CommunicationModel::FIELD_MODE, lbl_mode);
    
    emit CommunicationView::sig_View_Initialized(manager);
}
