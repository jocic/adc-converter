#include <QWidget>

#include "gen_widget.h"
#include "gen_model.h"
#include "gen_view.h"
#include "gen_controller.h"

GenWidget::GenWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void GenWidget::initialize() {
    
    m_Model      = new GenModel();
    m_View       = new GenView();
    m_Controller = new GenController();
    
    connect(m_Model, &GenModel::sig_Model_Updated,
        (GenController*)m_Controller, &GenController::on_Model_Changed);
    
    connect(m_Model, &GenModel::sig_Model_Cleared,
        (GenController*)m_Controller, &GenController::on_Model_Cleared);
    
    connect(m_View, &GenView::sig_View_Initialized,
        (GenController*)m_Controller, &GenController::on_View_Initialized);
    
    connect(m_View, &GenView::sig_View_Changed,
        (GenController*)m_Controller, &GenController::on_View_Changed);
    
    m_View->initialize(this);
}
