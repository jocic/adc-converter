#include <QWidget>

#include "smp_widget.h"
#include "smp_model.h"
#include "smp_view.h"
#include "smp_controller.h"

SmpWidget::SmpWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void SmpWidget::initialize() {
    
    m_Model      = new SmpModel();
    m_View       = new SmpView();
    m_Controller = new SmpController();
    
    m_Controller->set_Model(m_Model);
    m_Controller->set_View(m_View);
    
    connect(m_Model, &SmpModel::sig_Model_Updated,
        (SmpController*)m_Controller, &SmpController::on_Model_Changed);
    
    connect(m_Model, &SmpModel::sig_Model_Cleared,
        (SmpController*)m_Controller, &SmpController::on_Model_Cleared);
    
    connect(m_View, &SmpView::sig_View_Initialized,
        (SmpController*)m_Controller, &SmpController::on_View_Initialized);
    
    connect(m_View, &SmpView::sig_View_Changed,
        (SmpController*)m_Controller, &SmpController::on_View_Changed);
    
    m_View->initialize(this);
}
