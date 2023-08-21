#include "views/scope/scope_widget.h"
#include "views/scope/scope_view.h"
#include "views/scope/scope_controller.h"

ScopeWidget::ScopeWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void ScopeWidget::initialize() {
    
    m_View       = new ScopeView();
    m_Controller = new ScopeController();
    
    m_Controller->set_View(m_View);
    
    m_View->initialize(this);
}
