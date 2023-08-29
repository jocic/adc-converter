#include <QDebug>
#include <QLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>

#include "app/app_icons.h"
#include "app/mvc/element_manager.h"
#include "widgets/options/controls/controls_model.h"
#include "widgets/options/controls/controls_view.h"

void ControlsView::initialize(QWidget* parent) {
    
    // Arrange Controls
    
    QWidget*     wd_ctls  = new QWidget();
    QHBoxLayout* lay_ctls = new QHBoxLayout();
    QPushButton* btn_conn = new QPushButton();
    QPushButton* btn_ref  = new QPushButton();
    QPushButton* btn_sim  = new QPushButton();
    
    btn_conn->setText("Connect");
    btn_ref->setText("Refresh");
    
    btn_sim->setIcon(*AppIcons::SIMULATE);
    btn_sim->setMinimumWidth(35);
    btn_sim->setMaximumWidth(35);
    
    lay_ctls->setContentsMargins(0, 0, 0, 0);
    lay_ctls->addWidget(btn_conn);
    lay_ctls->addWidget(btn_ref);
    lay_ctls->addWidget(btn_sim);
    
    wd_ctls->setLayout(lay_ctls);
    
    // Arrange Timer
    
    QWidget*     wd_timer   = new QWidget();
    QHBoxLayout* lay_timer  = new QHBoxLayout();
    QLabel*      lbl_tmhead = new QLabel();
    QLabel*      lbl_tmval  = new QLabel();
    
    lbl_tmhead->setText("Time Active:");
    lbl_tmhead->setAlignment(Qt::AlignmentFlag::AlignRight);
    lbl_tmval->setText("00:00:00");
    lbl_tmval->setAlignment(Qt::AlignmentFlag::AlignLeft);
    
    lay_timer->addWidget(lbl_tmhead);
    lay_timer->addWidget(lbl_tmval);
    lay_timer->setContentsMargins(0, 5, 0, 0);
    
    wd_timer->setLayout(lay_timer);
    
    // Arrange View
    
    QWidget*     wd_root  = new QWidget();
    QVBoxLayout* lay_root = new QVBoxLayout();
    
    lay_root->addWidget(wd_ctls);
    lay_root->addWidget(wd_timer);
    
    wd_root->setLayout(lay_root);
    
    parent->layout()->addWidget(wd_root);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push(ControlsModel::FIELD_CONNECT, btn_conn);
    manager->push(ControlsModel::FIELD_REFRESH, btn_ref);
    manager->push(ControlsModel::FIELD_SIMULATE, btn_sim);
    manager->push(ControlsModel::FIELD_ACTIVE, lbl_tmval);
    
    emit ControlsView::sig_View_Initialized(manager);
}
