#include <QWidget>

#include "stream_widget.h"
#include "stream_model.h"
#include "stream_view.h"
#include "stream_controller.h"

StreamWidget::StreamWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void StreamWidget::initialize() {
    
    m_Model      = new StreamModel();
    m_View       = new StreamView();
    m_Controller = new StreamController();
    
    m_Controller->set_Model(m_Model);
    m_Controller->set_View(m_View);
    
    connect(m_Model, &StreamModel::sig_Model_Updated,
        (StreamController*)m_Controller, &StreamController::on_Model_Changed);
    
    connect(m_Model, &StreamModel::sig_Model_Cleared,
        (StreamController*)m_Controller, &StreamController::on_Model_Cleared);
    
    connect(m_View, &StreamView::sig_View_Initialized,
        (StreamController*)m_Controller, &StreamController::on_View_Initialized);
    
    connect(m_View, &StreamView::sig_View_Changed,
        (StreamController*)m_Controller, &StreamController::on_View_Changed);
    
    m_View->initialize(this);
}
