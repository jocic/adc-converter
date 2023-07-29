#include <QWidget>

#include "bps_widget.h"
#include "bps_model.h"
#include "bps_view.h"
#include "bps_controller.h"


BpsWidget::BpsWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void BpsWidget::initialize() {
    
    m_Model      = new BpsModel();
    m_View       = new BpsView();
    m_Controller = new BpsController();
    
    connect(m_Model, &BpsModel::sig_Model_Updated,
        (BpsController*)m_Controller, &BpsController::on_Model_Changed);
    
    connect(m_Model, &BpsModel::sig_Model_Cleared,
        (BpsController*)m_Controller, &BpsController::on_Model_Cleared);
    
    connect(m_View, &BpsView::sig_View_Initialized,
        (BpsController*)m_Controller, &BpsController::on_View_Initialized);
    
    connect(m_View, &BpsView::sig_View_Changed,
        (BpsController*)m_Controller, &BpsController::on_View_Changed);
    
    m_View->initialize(this);
}