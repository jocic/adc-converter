#include <QWidget>

#include "communication_widget.h"
#include "communication_model.h"
#include "communication_view.h"
#include "communication_controller.h"

CommunicationWidget::CommunicationWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void CommunicationWidget::initialize() {
    
    m_Model      = new CommunicationModel();
    m_View       = new CommunicationView();
    m_Controller = new CommunicationController();
    
    m_Controller->set_Model(m_Model);
    m_Controller->set_View(m_View);
    
    connect(m_Model, &CommunicationModel::sig_Model_Updated,
        (CommunicationController*)m_Controller, &CommunicationController::on_Model_Changed);
    
    connect(m_Model, &CommunicationModel::sig_Model_Cleared,
        (CommunicationController*)m_Controller, &CommunicationController::on_Model_Cleared);
    
    connect(m_View, &CommunicationView::sig_View_Initialized,
        (CommunicationController*)m_Controller, &CommunicationController::on_View_Initialized);
    
    connect(m_View, &CommunicationView::sig_View_Changed,
        (CommunicationController*)m_Controller, &CommunicationController::on_View_Changed);
    
    m_View->initialize(this);
}
