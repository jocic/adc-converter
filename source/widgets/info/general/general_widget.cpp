#include <QWidget>

#include "general_widget.h"
#include "general_model.h"
#include "general_view.h"
#include "general_controller.h"

GeneralWidget::GeneralWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void GeneralWidget::initialize() {
    
    m_Model      = new GeneralModel();
    m_View       = new GeneralView();
    m_Controller = new GeneralController();
    
    m_Controller->set_Model(m_Model);
    m_Controller->set_View(m_View);
    
    connect(m_Model, &GeneralModel::sig_Model_Updated,
        (GeneralController*)m_Controller, &GeneralController::on_Model_Changed);
    
    connect(m_Model, &GeneralModel::sig_Model_Cleared,
        (GeneralController*)m_Controller, &GeneralController::on_Model_Cleared);
    
    connect(m_View, &GeneralView::sig_View_Initialized,
        (GeneralController*)m_Controller, &GeneralController::on_View_Initialized);
    
    connect(m_View, &GeneralView::sig_View_Changed,
        (GeneralController*)m_Controller, &GeneralController::on_View_Changed);
    
    m_View->initialize(this);
}
