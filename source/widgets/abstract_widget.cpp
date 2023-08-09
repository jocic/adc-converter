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

QWidget* AbstractWidget::parent() {
    return m_Parent;
}

AbstractModel* AbstractWidget::model() {
    return m_Model;
}

AbstractView* AbstractWidget::view() {
    return m_View;
}

AbstractController* AbstractWidget::controller() {
    return m_Controller;
}
