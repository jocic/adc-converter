#include <QWidget>

#include "ref_widget.h"
#include "ref_model.h"
#include "ref_view.h"
#include "ref_controller.h"


RefWidget::RefWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void RefWidget::initialize() {
    
    m_Model      = new RefModel();
    m_View       = new RefView();
    m_Controller = new RefController();
    
    m_Controller->set_Model(m_Model);
    m_Controller->set_View(m_View);
    
    connect(m_Model, &RefModel::sig_Model_Updated,
        (RefController*)m_Controller, &RefController::on_Model_Changed);
    
    connect(m_Model, &RefModel::sig_Model_Cleared,
        (RefController*)m_Controller, &RefController::on_Model_Cleared);
    
    connect(m_View, &RefView::sig_View_Initialized,
        (RefController*)m_Controller, &RefController::on_View_Initialized);
    
    connect(m_View, &RefView::sig_View_Changed,
        (RefController*)m_Controller, &RefController::on_View_Changed);
    
    m_View->initialize(this);
}
