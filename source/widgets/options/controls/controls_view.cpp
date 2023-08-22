#include <QDebug>
#include <QLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include "app/app_icons.h"
#include "app/mvc/element_manager.h"
#include "widgets/options/controls/controls_model.h"
#include "widgets/options/controls/controls_view.h"

void ControlsView::initialize(QWidget* parent) {
    
    // Arrange View
    
    QWidget*     wd_root  = new QWidget();
    QHBoxLayout* lay_root = new QHBoxLayout();
    QPushButton* btn_conn = new QPushButton();
    QPushButton* btn_ref  = new QPushButton();
    QPushButton* btn_sim  = new QPushButton();
    
    btn_conn->setText("Connect");
    btn_ref->setText("Refresh");
    
    btn_sim->setIcon(*AppIcons::SIMULATE);
    btn_sim->setMaximumWidth(30);
    btn_sim->setToolTip("Simulate");
    
    lay_root->setContentsMargins(0, 0, 0, 0);
    lay_root->addWidget(btn_conn);
    lay_root->addWidget(btn_ref);
    lay_root->addWidget(btn_sim);
    
    wd_root->setLayout(lay_root);
    
    parent->layout()->addWidget(wd_root);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push(ControlsModel::FIELD_CONNECT, btn_conn);
    manager->push(ControlsModel::FIELD_REFRESH, btn_ref);
    manager->push(ControlsModel::FIELD_SIMULATE, btn_sim);
    
    emit ControlsView::sig_View_Initialized(manager);
}
