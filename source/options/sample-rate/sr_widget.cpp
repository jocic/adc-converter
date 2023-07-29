#include <QWidget>

#include "sr_widget.h"
//#include "sr_model.h"
#include "sr_view.h"
//#include "sr_controller.h"


SrWidget::SrWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void SrWidget::initialize() {
    
    m_View = new SrView();
    
    m_View->initialize(this);
}
