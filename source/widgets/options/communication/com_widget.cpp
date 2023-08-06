#include <QWidget>

#include "com_widget.h"
#include "com_model.h"
#include "com_view.h"
#include "com_controller.h"

ComWidget::ComWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void ComWidget::initialize() {
    
    m_Model      = new ComModel();
    m_View       = new ComView();
    m_Controller = new CommunicationController();
    
    m_Controller->set_Model(m_Model);
    m_Controller->set_View(m_View);
    
    connect(m_Model, &ComModel::sig_Model_Updated,
        (CommunicationController*)m_Controller, &CommunicationController::on_Model_Changed);
    
    connect(m_Model, &ComModel::sig_Model_Cleared,
        (CommunicationController*)m_Controller, &CommunicationController::on_Model_Cleared);
    
    connect(m_View, &ComView::sig_View_Initialized,
        (CommunicationController*)m_Controller, &CommunicationController::on_View_Initialized);
    
    connect(m_View, &ComView::sig_View_Changed,
        (CommunicationController*)m_Controller, &CommunicationController::on_View_Changed);
    
    m_View->initialize(this);
}
