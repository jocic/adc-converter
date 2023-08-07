#include <QDebug>
#include <QLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>

#include "mvc/element_manager.h"
#include "processing_model.h"
#include "processing_view.h"

void ProcessingView::initialize(QWidget* parent) {
    
    // Arrange View
    
    QWidget*      wd_main     = new QWidget();
    QVBoxLayout*  lay_main    = new QVBoxLayout();
    QLabel*       lbl_notice  = new QLabel();
    QProgressBar* pb_progress = new QProgressBar();
    QPushButton*  btn_cancel  = new QPushButton();
    
    lbl_notice->setText(m_Notice);
    
    pb_progress->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    pb_progress->setValue(0);
    
    btn_cancel->setText("Cancel");
    
    lay_main->addWidget(lbl_notice);    
    lay_main->addWidget(pb_progress);
    lay_main->addWidget(this->make_HLine());
    lay_main->addWidget(btn_cancel);
    lay_main->setSpacing(10);
    
    wd_main->setLayout(lay_main);
    
    parent->layout()->addWidget(wd_main);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push(ProcessingModel::FIELD_PROGRESS, pb_progress);
    manager->push(ProcessingModel::FIELD_CANCEL, btn_cancel);
    
    emit ProcessingView::sig_View_Initialized(manager);
}

QString ProcessingView::get_Notice() {
    return m_Notice;
}

void ProcessingView::set_Notice(QString value) {
    m_Notice = value;
}
