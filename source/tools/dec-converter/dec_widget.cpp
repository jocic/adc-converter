#include <QWidget>

#include "dec_widget.h"
#include "dec_model.h"
#include "dec_view.h"
#include "dec_controller.h"


DecWidget::DecWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void DecWidget::initialize() {
    
    m_Model      = new DecModel();
    m_View       = new DecView();
    m_Controller = new DecController();
    
    connect(m_Model, &DecModel::sig_Model_Updated,
        (DecController*)m_Controller, &DecController::on_Model_Changed);
    
    connect(m_Model, &DecModel::sig_Model_Cleared,
        (DecController*)m_Controller, &DecController::on_Model_Cleared);
    
    connect(m_View, &DecView::sig_View_Initialized,
        (DecController*)m_Controller, &DecController::on_View_Initialized);
    
    connect(m_View, &DecView::sig_View_Changed,
        (DecController*)m_Controller, &DecController::on_View_Changed);
    
    m_View->initialize(this);
}
