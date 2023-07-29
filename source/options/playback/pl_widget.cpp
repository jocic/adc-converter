#include <QWidget>

#include "pl_widget.h"
//#include "pl_model.h"
#include "pl_view.h"
//#include "pl_controller.h"

PlWidget::PlWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void PlWidget::initialize() {
    
    m_View = new PlView();
    
    m_View->initialize(this);
}
