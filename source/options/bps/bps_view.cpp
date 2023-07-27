#include <QDebug>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QComboBox>
#include <QCheckBox>

#include "mvc/element_manager.h"
#include "bps_view.h"

void BpsView::initialize(QWidget* parent) {
    
    // Arrange View
    
    QGroupBox*   box    = new QGroupBox();
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
    
    parent->layout()->addWidget(box);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push("combo_BitsPerSample", combo);
    manager->push("cbeck_Signed", check);
    
    emit BpsView::sig_View_Initialized();
}
