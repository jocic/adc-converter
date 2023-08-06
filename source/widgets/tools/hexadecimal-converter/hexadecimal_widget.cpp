#include <QWidget>

#include "hexadecimal_widget.h"
#include "hexadecimal_model.h"
#include "hexadecimal_view.h"
#include "hexadecimal_controller.h"

HexadecimalWidget::HexadecimalWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void HexadecimalWidget::initialize() {
    
    m_Model      = new HexadecimalModel();
    m_View       = new HexadecimalView();
    m_Controller = new HexadecimalController();
    
    m_Controller->set_Model(m_Model);
    m_Controller->set_View(m_View);
    
    connect(m_Model, &HexadecimalModel::sig_Model_Updated,
        (HexadecimalController*)m_Controller, &HexadecimalController::on_Model_Changed);
    
    connect(m_Model, &HexadecimalModel::sig_Model_Cleared,
        (HexadecimalController*)m_Controller, &HexadecimalController::on_Model_Cleared);
    
    connect(m_View, &HexadecimalView::sig_View_Initialized,
        (HexadecimalController*)m_Controller, &HexadecimalController::on_View_Initialized);
    
    connect(m_View, &HexadecimalView::sig_View_Changed,
        (HexadecimalController*)m_Controller, &HexadecimalController::on_View_Changed);
    
    m_View->initialize(this);
}
