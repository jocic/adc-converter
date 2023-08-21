#include "views/scope/scope_widget.h"
#include "views/scope/scope_view.h"

ScopeWidget::ScopeWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void ScopeWidget::initialize() {
    
    m_View       = new ScopeView();
    m_View->initialize(this);
}
