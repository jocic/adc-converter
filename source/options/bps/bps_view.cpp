#include <QDebug>

#include "bps_view.h"

void BpsView::initialize(QWidget* parent) {
    
    QGroupBox*   box    = new QGroupBox();
    QFormLayout* layout = new QFormLayout();
    QComboBox*   combo  = new QComboBox();
    QCheckBox*   check  = new QCheckBox();
    
    // Box Layout
    
//        m_ElementManager->insert("group_box", box);
     {
        parent->layout()->addWidget(box);
    }
    
    parent->setStyleSheet("");
    box->setLayout(layout);
    box->setTitle("Bits Per Sample");
    
    combo->addItems({
        "8", "16", "24", "32"
    });
    
    check->setText("Signed");
    
    layout->addRow(combo, check);
    
    this->arrange();
    
    qDebug() << "[*] BpsView (AbstractView) - Initialized";
    
    emit BpsView::sig_View_Initialized();
}


void BpsView::arrange() {
    return;
    QGroupBox*   box    = new QGroupBox(); // m_ElementManager->get("group_box")
    QFormLayout* layout = new QFormLayout();
    QComboBox*   combo  = new QComboBox();
    QCheckBox*   check  = new QCheckBox();
    
    box->setLayout(layout);
    box->setTitle("Bits Per Sample");
    
    combo->addItems({
        "8", "16", "24", "32"
    });
    
    check->setText("Signed");
    
    layout->addRow(combo, check);
    
    
    qDebug() << "[*] BpsView (AbstractView) - Arranged";
    
    emit BpsView::sig_View_Arranged();
}
