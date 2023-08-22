#include <QWidget>

#include "widgets/options/controls/controls_widget.h"
#include "widgets/options/controls/controls_model.h"
#include "widgets/options/controls/controls_view.h"
#include "widgets/options/controls/controls_controller.h"

ControlsWidget::ControlsWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void ControlsWidget::initialize() {
    
    m_Model      = new ControlsModel();
    m_View       = new ControlsView();
    m_Controller = new ControlsController();
    
    m_Controller->set_Model(m_Model);
    m_Controller->set_View(m_View);
    
    connect(m_Model, &ControlsModel::sig_Model_Updated,
        (ControlsController*)m_Controller, &ControlsController::on_Model_Changed);
    
    connect(m_Model, &ControlsModel::sig_Model_Cleared,
        (ControlsController*)m_Controller, &ControlsController::on_Model_Cleared);
    
    connect(m_View, &ControlsView::sig_View_Initialized,
        (ControlsController*)m_Controller, &ControlsController::on_View_Initialized);
    
    connect(m_View, &ControlsView::sig_View_Changed,
        (ControlsController*)m_Controller, &ControlsController::on_View_Changed);
    
    m_View->initialize(this);
}
