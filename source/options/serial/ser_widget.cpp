#include <QWidget>

#include "ser_widget.h"
#include "ser_model.h"
#include "ser_view.h"
#include "ser_controller.h"

SerWidget::SerWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void SerWidget::initialize() {
    
    m_Model      = new SerModel();
    m_View       = new SerView();
    m_Controller = new SerController();
    
    connect(m_Model, &SerModel::sig_Model_Updated,
        (SerController*)m_Controller, &SerController::on_Model_Changed);
    
    connect(m_Model, &SerModel::sig_Model_Cleared,
        (SerController*)m_Controller, &SerController::on_Model_Cleared);
    
    connect(m_View, &SerView::sig_View_Initialized,
        (SerController*)m_Controller, &SerController::on_View_Initialized);
    
    connect(m_View, &SerView::sig_View_Changed,
        (SerController*)m_Controller, &SerController::on_View_Changed);
    
    m_View->initialize(this);
}
