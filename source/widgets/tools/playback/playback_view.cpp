#include <QDebug>
#include <QIcon>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QSlider>
#include <QPushButton>

#include "app/mvc/element_manager.h"
#include "app/app_icons.h"
#include "playback_model.h"
#include "playback_view.h"

void PlaybackView::initialize(QWidget* parent) {
    
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
    layout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    
    parent->layout()->addWidget(box);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push(PlaybackModel::FIELD_PLAYBACK_TIME, slider);
    manager->push(PlaybackModel::FIELD_TOGGLE, toggle);
    manager->push(PlaybackModel::FIELD_EXPORT, save);
    
    emit PlaybackView::sig_View_Initialized(manager);
}
