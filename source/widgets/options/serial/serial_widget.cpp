#include <QWidget>

#include "serial_widget.h"
#include "serial_model.h"
#include "serial_view.h"
#include "serial_controller.h"

SerialWidget::SerialWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void SerialWidget::initialize() {
    
    m_Model      = new SerialModel();
    m_View       = new SerialView();
    m_Controller = new SerialController();
    
    m_Controller->set_Model(m_Model);
    m_Controller->set_View(m_View);
    
    connect(m_Model, &SerialModel::sig_Model_Updated,
        (SerialController*)m_Controller, &SerialController::on_Model_Changed);
    
    connect(m_Model, &SerialModel::sig_Model_Cleared,
        (SerialController*)m_Controller, &SerialController::on_Model_Cleared);
    
    connect(m_View, &SerialView::sig_View_Initialized,
        (SerialController*)m_Controller, &SerialController::on_View_Initialized);
    
    connect(m_View, &SerialView::sig_View_Changed,
        (SerialController*)m_Controller, &SerialController::on_View_Changed);
    
    m_View->initialize(this);
}
