#include <QWidget>

#include "sr_widget.h"
#include "sr_model.h"
#include "sr_view.h"
#include "sr_controller.h"

SrWidget::SrWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void SrWidget::initialize() {
    
    m_Model      = new SrModel();
    m_View       = new SrView();
    m_Controller = new SrController();
    
    connect(m_Model, &SrModel::sig_Model_Updated,
        (SrController*)m_Controller, &SrController::on_Model_Changed);
    
    connect(m_Model, &SrModel::sig_Model_Cleared,
        (SrController*)m_Controller, &SrController::on_Model_Cleared);
    
    connect(m_View, &SrView::sig_View_Initialized,
        (SrController*)m_Controller, &SrController::on_View_Initialized);
    
    connect(m_View, &SrView::sig_View_Changed,
        (SrController*)m_Controller, &SrController::on_View_Changed);
    
    m_View->initialize(this);
}
