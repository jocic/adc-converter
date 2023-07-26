#include "bps_widget.h"


BpsWidget::BpsWidget(QWidget* parent) {
    
    m_Parent = parent;
    
    m_View = new BpsView();
    
    initialize();
}

void BpsWidget::initialize() {
    
    m_View->setup(m_Parent);
}

const BpsModel* BpsWidget::model() {
    return m_Model;
}

const BpsView* BpsWidget::view() {
    return m_View;
}

const BpsController* BpsWidget::controller() {
    return m_Controller;
}
