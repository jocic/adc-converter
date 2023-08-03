#include <QDebug>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

#include "mvc/element_manager.h"
#include "com_model.h"
#include "com_view.h"

void ComView::initialize(QWidget* parent) {
    
    // Arrange View
    
    QGroupBox*   box      = new QGroupBox();
    QFormLayout* lay_root = new QFormLayout();
    QLabel*      lbl_port = new QLabel();
    QComboBox*   cmb_port = new QComboBox();
    QLabel*      lbl_mode = new QLabel();
    QComboBox*   cmb_mode = new QComboBox();
    QWidget*     wd_opt   = new QWidget();
    QPushButton* btn_conn = new QPushButton();
    QPushButton* btn_ref  = new QPushButton();
    
    box->setLayout(lay_root);
    box->setTitle("Communication");
    
    lbl_port->setText("COM Port");
    lay_root->addRow(lbl_port, cmb_port);
    
    lbl_mode->setText("COM Mode");
    cmb_mode->addItems({ "Text", "Binary" });
    lay_root->addRow(lbl_mode, cmb_mode);
    
    btn_conn->setText("Connect");
    btn_ref->setText("Refresh");
    wd_opt->setLayout(new QHBoxLayout());
    wd_opt->layout()->setContentsMargins(0, 0, 0, 0);
    wd_opt->layout()->addWidget(btn_conn);
    wd_opt->layout()->addWidget(btn_ref);
    
    parent->layout()->addWidget(box);
    parent->layout()->addWidget(wd_opt);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push(ComModel::FIELD_PORT, cmb_port);
    manager->push(ComModel::FIELD_MODE, lbl_mode);
    
    emit ComView::sig_View_Initialized(manager);
}
