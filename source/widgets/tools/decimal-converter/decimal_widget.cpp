#include <QWidget>

#include "decimal_widget.h"
#include "decimal_model.h"
#include "decimal_view.h"
#include "decimal_controller.h"

DecimalWidget::DecimalWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void DecimalWidget::initialize() {
    
    m_Model      = new DecimalModel();
    m_View       = new DecimalView();
    m_Controller = new DecimalController();
    
    m_Controller->set_Model(m_Model);
    m_Controller->set_View(m_View);
    
    connect(m_Model, &DecimalModel::sig_Model_Updated,
        (DecimalController*)m_Controller, &DecimalController::on_Model_Changed);
    
    connect(m_Model, &DecimalModel::sig_Model_Cleared,
        (DecimalController*)m_Controller, &DecimalController::on_Model_Cleared);
    
    connect(m_View, &DecimalView::sig_View_Initialized,
        (DecimalController*)m_Controller, &DecimalController::on_View_Initialized);
    
    connect(m_View, &DecimalView::sig_View_Changed,
        (DecimalController*)m_Controller, &DecimalController::on_View_Changed);
    
    m_View->initialize(this);
}
