#include <QDebug>
#include <QIcon>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QSlider>
#include <QPushButton>

#include "mvc/element_manager.h"
#include "app_icons.h"
//#include "pl_model.h"
#include "pl_view.h"

void PlView::initialize(QWidget* parent) {
    
    // Arrange View
    
    QGroupBox*   box    = new QGroupBox();
    QFormLayout* layout = new QFormLayout();
    QSlider*     slider = new QSlider();
    QPushButton* toggle = new QPushButton();
    QPushButton* save   = new QPushButton();
    
    box->setLayout(layout);
    box->setTitle("Playback");
    
    slider->setOrientation(Qt::Orientation::Horizontal);
    
    toggle->setText("Play");
    toggle->setIcon(*AppIcons::PLAY);
    
    save->setText("Export");    
    save->setIcon(*AppIcons::EXPORT);
    
    layout->addRow(slider);
    layout->addRow(toggle, save);
    
    parent->layout()->addWidget(box);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    //manager->push(BpsModel::FIELD_BITS_PER_SAMPLE, combo);
    //manager->push(BpsModel::FIELD_SIGNED, check);
    
    emit PlView::sig_View_Initialized(manager);
}
