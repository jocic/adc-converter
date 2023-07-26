#ifndef ADC_OPTIONS_BPS_VIEW

#define ADC_OPTIONS_BPS_VIEW

#include <QWidget>
#include <QGroupBox>
#include <QFormLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>

class BpsView {
    
public:
    
    void setup(QWidget* parent) {
        
        QGroupBox*   box    = new QGroupBox();
        QFormLayout* layout = new QFormLayout();
        QComboBox*   combo  = new QComboBox();
        QCheckBox*   check  = new QCheckBox();
        
        // Box Layout
        
//        m_ElementManager->insert("group_box", box);
        
        arrange(parent);
        
    }
    
    void arrange(QWidget* parent) {
        
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
        
        parent->layout()->addWidget(box);
    }
};

#endif
