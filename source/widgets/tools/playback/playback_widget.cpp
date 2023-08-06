#include <QWidget>

#include "playback_widget.h"
//#include "playback_model.h"
#include "playback_view.h"
//#include "playback_controller.h"

PlaybackWidget::PlaybackWidget(QWidget* parent) : AbstractWidget(parent)  {
    
    // Nothing here, yet...
}

void PlaybackWidget::initialize() {
    
    m_View = new PlaybackView();
    
    m_View->initialize(this);
}
