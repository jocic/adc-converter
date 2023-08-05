#include <QWidget>

#include "hex_widget.h"
#include "hex_model.h"
#include "hex_view.h"
#include "hex_controller.h"


HexWidget::HexWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void HexWidget::initialize() {
    
    m_Model      = new HexModel();
    m_View       = new HexView();
    m_Controller = new HexController();
    
    m_Controller->set_Model(m_Model);
    
    connect(m_Model, &HexModel::sig_Model_Updated,
        (HexController*)m_Controller, &HexController::on_Model_Changed);
    
    connect(m_Model, &HexModel::sig_Model_Cleared,
        (HexController*)m_Controller, &HexController::on_Model_Cleared);
    
    connect(m_View, &HexView::sig_View_Initialized,
        (HexController*)m_Controller, &HexController::on_View_Initialized);
    
    connect(m_View, &HexView::sig_View_Changed,
        (HexController*)m_Controller, &HexController::on_View_Changed);
    
    m_View->initialize(this);
}
