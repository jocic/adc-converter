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
    
    connect(m_View, &ScopeView::sig_View_Initialized,
        (ScopeController*)m_Controller, &ScopeController::on_View_Initialized);
    
    connect(m_View, &ScopeView::sig_View_Changed,
        (ScopeController*)m_Controller, &ScopeController::on_View_Changed);
    
    m_View->initialize(this);
}
