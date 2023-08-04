#include <QWidget>
#include <QVBoxLayout>

#include "widgets/abstract_widget.h"

AbstractWidget::AbstractWidget(QWidget* parent) {
    
    m_Parent = parent;
    
    m_Model      = NULL;
    m_View       = NULL;
    m_Controller = NULL;
    
    this->setLayout(new QVBoxLayout());
    
    this->layout()->setContentsMargins(0, 0, 0, 0);
}

const AbstractModel* AbstractWidget::model() {
    return m_Model;
}

const AbstractView* AbstractWidget::view() {
    return m_View;
}

const AbstractController* AbstractWidget::controller() {
    return m_Controller;
}
