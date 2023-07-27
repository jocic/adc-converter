#include "bps_widget.h"
#include "bps_model.h"
#include "bps_view.h"
#include "bps_controller.h"

#include <QDebug>
#include <QHBoxLayout>

void BpsWidget::initialize() {
    
    m_Model      = new BpsModel();
    m_View       = new BpsView();
    m_Controller = new BpsController();
    
    m_View->initialize(this);
    
    qDebug() << "BpsWidget (AbstractWidget) - Initialized";
}
