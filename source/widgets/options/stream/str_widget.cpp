#include <QWidget>

#include "str_widget.h"
#include "str_model.h"
#include "str_view.h"
#include "str_controller.h"

StrWidget::StrWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void StrWidget::initialize() {
    
    m_Model      = new StrModel();
    m_View       = new StrView();
    m_Controller = new StrController();
    
    m_Controller->set_Model(m_Model);
    m_Controller->set_View(m_View);
    
    connect(m_Model, &StrModel::sig_Model_Updated,
        (StrController*)m_Controller, &StrController::on_Model_Changed);
    
    connect(m_Model, &StrModel::sig_Model_Cleared,
        (StrController*)m_Controller, &StrController::on_Model_Cleared);
    
    connect(m_View, &StrView::sig_View_Initialized,
        (StrController*)m_Controller, &StrController::on_View_Initialized);
    
    connect(m_View, &StrView::sig_View_Changed,
        (StrController*)m_Controller, &StrController::on_View_Changed);
    
    m_View->initialize(this);
}
