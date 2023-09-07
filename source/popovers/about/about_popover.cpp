#include <QWidget>
#include <QProgressBar>

#include "about_popover.h"
#include "about_view.h"

AboutPopover::AboutPopover(QWidget* parent) : AbstractPopover(parent)  {
    
    m_Parent = parent;
}

void AboutPopover::initialize() {
    
    this->setWindowTitle("About ADC Converter");
    this->setMaximumHeight(150);
    this->setMaximumWidth(300);
    
    ///////////////////////////
    
    m_View = new AboutView();
    
    m_View->initialize(this);
}
