#include <QWidget>

#include "playback_widget.h"
#include "playback_model.h"
#include "playback_view.h"
#include "playback_controller.h"

PlaybackWidget::PlaybackWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void PlaybackWidget::initialize() {
    
    m_Model      = new PlaybackModel();
    m_View       = new PlaybackView();
    m_Controller = new PlaybackController();
    
    m_Controller->set_Model(m_Model);
    m_Controller->set_View(m_View);
    
    connect(m_Model, &PlaybackModel::sig_Model_Updated,
        (PlaybackController*)m_Controller, &PlaybackController::on_Model_Changed);
    
    connect(m_Model, &PlaybackModel::sig_Model_Cleared,
        (PlaybackController*)m_Controller, &PlaybackController::on_Model_Cleared);
    
    connect(m_View, &PlaybackView::sig_View_Initialized,
        (PlaybackController*)m_Controller, &PlaybackController::on_View_Initialized);
    
    connect(m_View, &PlaybackView::sig_View_Changed,
        (PlaybackController*)m_Controller, &PlaybackController::on_View_Changed);
    
    m_View->initialize(this);
}
