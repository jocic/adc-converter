#include <QWidget>

#include "reference_widget.h"
#include "reference_model.h"
#include "reference_view.h"
#include "reference_controller.h"


ReferenceWidget::ReferenceWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void ReferenceWidget::initialize() {
    
    m_Model      = new ReferenceModel();
    m_View       = new ReferenceView();
    m_Controller = new ReferenceController();
    
    m_Controller->set_Model(m_Model);
    m_Controller->set_View(m_View);
    
    connect(m_Model, &ReferenceModel::sig_Model_Updated,
        (ReferenceController*)m_Controller, &ReferenceController::on_Model_Changed);
    
    connect(m_Model, &ReferenceModel::sig_Model_Cleared,
        (ReferenceController*)m_Controller, &ReferenceController::on_Model_Cleared);
    
    connect(m_View, &ReferenceView::sig_View_Initialized,
        (ReferenceController*)m_Controller, &ReferenceController::on_View_Initialized);
    
    connect(m_View, &ReferenceView::sig_View_Changed,
        (ReferenceController*)m_Controller, &ReferenceController::on_View_Changed);
    
    m_View->initialize(this);
}
