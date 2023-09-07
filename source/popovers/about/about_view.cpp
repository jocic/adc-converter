#include <QDebug>
#include <QFont>
#include <QLayout>
#include <QFormLayout>
#include <QLabel>
#include <QTextBrowser>
#include <QProgressBar>
#include <QPushButton>

#include "app/mvc/element_manager.h"
#include "popovers/about/about_view.h"

void AboutView::initialize(QWidget* parent) {
    
    QFont* font_bold = this->make_BFont();
    
    // Arrange View
    
    QWidget*      wd_main        = new QWidget();
    QFormLayout*  lay_main       = new QFormLayout();
    QLabel*       lbl_name       = new QLabel();
    QLabel*       lbl_author     = new QLabel();
    QLabel*       lbl_author_val = new QLabel();
    QTextBrowser* txt_copyright  = new QTextBrowser();
    
    lbl_name->setText("ADC Converter 1.0.0");
    lbl_name->setFont(*font_bold);
    
    lbl_author->setText("Author:");
    lbl_author->setFont(*font_bold);
    lbl_author_val->setText("Đorđe Jocić");
    
    txt_copyright->setStyleSheet("background: transparent");
    txt_copyright->setFrameStyle(QFrame::Shape::NoFrame);
    txt_copyright->setText("This program is provided AS IS with no WARRANTY "
        "OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY "
        "AND FITNESS FOR A PARTICULAR PURPOSE.");
    
    lay_main->addRow(lbl_name);
    lay_main->addRow(lbl_author, lbl_author_val);
    lay_main->addRow(txt_copyright);
    
    wd_main->setLayout(lay_main);
    
    parent->layout()->addWidget(wd_main);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    emit AboutView::sig_View_Initialized(manager);
}
