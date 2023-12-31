#include <QDebug>
#include <QFrame>
#include <QWidget>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QVector>

#include "app/mvc/element_manager.h"
#include "elements/hex_viewer.h"
#include "samples_model.h"
#include "samples_view.h"

QVector<QLabel*> hexvals;

void SamplesView::initialize(QWidget* parent) {
    
    // Initialize Hex Viewer
    
    m_Viewer = new HexViewer(6000);
    
    // Arrange Controls
    
    QWidget*     wd_ctl   = new QWidget();
    QHBoxLayout* lay_ctl  = new QHBoxLayout();
    
    QWidget* wd_overview  = this->make_Overview();
    QWidget* wd_navigator = this->make_Navigator();
    QWidget* wd_offseter  = this->make_Offseter();
    
    lay_ctl->addWidget(wd_navigator);
    lay_ctl->addWidget(this->make_VLine());
    lay_ctl->addWidget(wd_offseter);
    lay_ctl->setContentsMargins(0, 0, 0, 0);
    
    wd_ctl->setLayout(lay_ctl);
    
    // Arrange View
    
    QWidget*     wd_main  = new QWidget();
    QVBoxLayout* lay_main = new QVBoxLayout();
    
    lay_main->addWidget(wd_overview);
    wd_main->setLayout(lay_main);
    
    parent->layout()->addWidget(wd_main);
    parent->layout()->addWidget(wd_ctl);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    emit SamplesView::sig_View_Initialized(manager);
}

HexViewer* SamplesView::get_HexViewer() {
    return m_Viewer;
}

QWidget* SamplesView::make_Overview() {
    
    QWidget*     wd_main  = new QWidget();
    QVBoxLayout* lay_main = new QVBoxLayout();
    QScrollArea* sa_main  = new QScrollArea();
    
    if (m_Viewer == NULL) {
        m_Viewer = new HexViewer();
    }
    
    sa_main->setWidgetResizable(true);
    sa_main->setWidget(m_Viewer);
    
    lay_main->addWidget(sa_main);
    wd_main->setLayout(lay_main);
    
    return wd_main;
}

QWidget* SamplesView::make_Navigator() {
    
    // Prev & Next Controls
    
    QPushButton* btn_prev = new QPushButton();
    QPushButton* btn_next = new QPushButton();
    
    btn_prev->setText("Prev");
    btn_next->setText("Next");
    
    // Page Details
    
    QWidget*     wd_details  = new QWidget();
    QGridLayout* lay_details = new QGridLayout();
    QLabel*      lbl_samp    = new QLabel();
    QLabel*      lbl_time    = new QLabel();
    QLabel*      lbl_sampv   = new QLabel();
    QLabel*      lbl_timev   = new QLabel();
    
    QFont* fnt_Bold = this->make_BFont();
    
    lbl_samp->setText("Samples:");
    lbl_samp->setFont(*fnt_Bold);
    
    lbl_time->setText("Time:");
    lbl_time->setFont(*fnt_Bold);
    
    lbl_sampv->setText("1 - 48");
    lbl_timev->setText("0 - 5");
    
    lay_details->addWidget(lbl_samp, 0, 0);
    lay_details->addWidget(lbl_sampv, 0, 1);
    lay_details->addWidget(lbl_time, 1, 0);
    lay_details->addWidget(lbl_timev, 1, 1);
    
    wd_details->setLayout(lay_details);
    
    // Arrange Elements
    
    QWidget*     wd_main  = new QWidget();
    QHBoxLayout* lay_main = new QHBoxLayout();
    
    lay_main->addSpacerItem(this->make_HSpacer());
    lay_main->addWidget(btn_prev);
    lay_main->addWidget(wd_details);
    lay_main->addWidget(btn_next);
    lay_main->addSpacerItem(this->make_HSpacer());
    
    wd_main->setLayout(lay_main);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push(SamplesModel::FIELD_PREV, btn_prev);
    manager->push(SamplesModel::FIELD_NEXT, btn_next);
    
    manager->push(SamplesModel::VALUE_SAMPLES, lbl_sampv);
    manager->push(SamplesModel::VALUE_TIME, lbl_timev);
    
    return wd_main;
}

QWidget* SamplesView::make_Offseter() {
    
    QWidget*     wd_main  = new QWidget();
    QHBoxLayout* lay_main = new QHBoxLayout();
    
    // Range Span
    
    QWidget*     wd_start  = new QWidget();
    QVBoxLayout* lay_start = new QVBoxLayout();
    QLabel*      lbl_start = new QLabel();
    QLineEdit*   txt_start = new QLineEdit();
    
    lbl_start->setText("Offset Start");
    txt_start->setText("0");
    txt_start->setMaximumWidth(75);
    
    lay_start->addWidget(lbl_start);
    lay_start->addWidget(txt_start);
    
    wd_start->setLayout(lay_start);
    
    // Range Span
    
    QWidget*     wd_span  = new QWidget();
    QVBoxLayout* lay_span = new QVBoxLayout();
    QLabel*      lbl_span = new QLabel();
    QComboBox*   cb_span  = new QComboBox();
    
    lbl_span->setText("Range Span");
    cb_span->addItems({ "48", "96", "144" });
    cb_span->setMaximumWidth(100);
    
    lay_span->addWidget(lbl_span);
    lay_span->addWidget(cb_span);
    
    wd_span->setLayout(lay_span);
    
    // Controls
    
    QWidget*     wd_ctls    = new QWidget();
    QVBoxLayout* lay_ctls   = new QVBoxLayout();
    QLabel*      lbl_offset = new QLabel();
    QPushButton* btn_offset = new QPushButton();
    
    btn_offset->setText("Offset");
    
    lay_ctls->addWidget(lbl_offset);
    lay_ctls->addWidget(btn_offset);
    
    wd_ctls->setLayout(lay_ctls);
    
    // Arrange Elements
    
    lay_main->addSpacerItem(this->make_HSpacer());
    lay_main->addWidget(wd_start);
    lay_main->addWidget(wd_span);
    lay_main->addWidget(wd_ctls);
    lay_main->addSpacerItem(this->make_HSpacer());
    
    wd_main->setLayout(lay_main);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push(SamplesModel::FIELD_OFFSET_START, txt_start);
    manager->push(SamplesModel::FIELD_RANGE_SPAN, cb_span);
    manager->push(SamplesModel::FIELD_OFFSET, btn_offset);
    
    return wd_main;
}
