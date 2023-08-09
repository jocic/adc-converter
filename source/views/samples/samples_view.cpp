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

#include "mvc/element_manager.h"
#include "elements/hex_viewer.h"
#include "samples_model.h"
#include "samples_view.h"

QVector<QLabel*> hexvals;

void SamplesView::initialize(QWidget* parent) {
    
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
    
    //manager->push(SmpView::FIELD_, );
    //manager->push(SmpView::FIELD_, );
    
    emit SamplesView::sig_View_Initialized(manager);
}

QWidget* SamplesView::make_Overview() {
    
    QWidget*     wd_main  = new QWidget();
    QVBoxLayout* lay_main = new QVBoxLayout();
    QScrollArea* sa_main  = new QScrollArea();
    
    QWidget* wd_table = this->make_Table();
    
    sa_main->setWidgetResizable(true);
    sa_main->setWidget(wd_table);
    
    lay_main->addWidget(sa_main);
    wd_main->setLayout(lay_main);
    
    return wd_main;
}

QWidget* SamplesView::make_Table() {
    
    return new HexViewer(100);
    // Arrange Columns
    
    QWidget*     wd_offset = new QWidget();
    QVBoxLayout* lay_offset = new QVBoxLayout();
    QWidget*     wd_samples = new QWidget();
    QVBoxLayout* lay_samples = new QVBoxLayout();
    QWidget*     wd_convs = new QWidget();
    QVBoxLayout* lay_convs = new QVBoxLayout();
    
    wd_offset->setStyleSheet("background: #e3e6e8");
    wd_offset->setLayout(lay_offset);
    
    wd_samples->setStyleSheet("background: #fff");
    wd_samples->setLayout(lay_samples);
    
    wd_convs->setStyleSheet("background: #fff");
    wd_convs->setLayout(lay_convs);
    
    lay_offset->setContentsMargins(0, 0, 0, 0);
    lay_samples->setContentsMargins(0, 0, 0, 0);
    lay_convs->setContentsMargins(0, 0, 0, 0);
    
    // Arrange Labels
    
    for (int i = 0; i < 80; i++) {
        
        QWidget*     wd_off  = new QWidget();
        QHBoxLayout* lay_off = new QHBoxLayout();
        QWidget*     wd_hex  = new QWidget();
        QHBoxLayout* lay_hex = new QHBoxLayout();
        QWidget*     wd_dec  = new QWidget();
        QHBoxLayout* lay_dec = new QHBoxLayout();
        
        QLabel* lbl_offset = new QLabel();
        
        lbl_offset->setText("00000000");
        
        lay_off->setContentsMargins(6, 3, 6, 3);
        lay_hex->setContentsMargins(6, 3, 6, 3);
        lay_dec->setContentsMargins(6, 3, 6, 3);
        
        wd_off->setLayout(lay_off);
        wd_hex->setLayout(lay_hex);
        wd_dec->setLayout(lay_dec);
        
        lay_off->addWidget(lbl_offset);
        
        for (int j = 0; j < 8; j++) {
            
            QLabel* lbl_hex = new QLabel();
            QLabel* lbl_dec = new QLabel();
            
            lbl_hex->setText(".");
            lbl_hex->setMinimumWidth(15);
            lbl_hex->setAlignment(Qt::AlignHCenter);
            lbl_hex->setMouseTracking(true);
            
            hexvals.push_back(lbl_hex);
            hexvals.push_back(lbl_dec);
            
            lbl_dec->setText(".");
            lbl_dec->setMinimumWidth(15);
            lbl_dec->setAlignment(Qt::AlignHCenter);
            
            lay_hex->addWidget(lbl_hex);
            lay_dec->addWidget(lbl_dec);
        }
        
        lay_offset->addWidget(wd_off);
        lay_samples->addWidget(wd_hex);
        lay_convs->addWidget(wd_dec);
    }
    
    // Arrange Elements
    
    QWidget*     wd_main  = new QWidget();
    QHBoxLayout* lay_main = new QHBoxLayout();
    
    lay_main->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
    
    lay_main->addWidget(wd_offset);
    lay_main->addWidget(wd_samples);
    lay_main->addWidget(wd_convs);
    
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
    
    lbl_sampv->setText("1 - 1001");
    lbl_timev->setText("0 - 1");
    
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
    cb_span->addItems({ "28", "56", "112" });
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


QVector<QLabel*>* SamplesView::test() {
    return &hexvals;
}
