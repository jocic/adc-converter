#include <QWidget>
#include <QVBoxLayout>

#include "popovers/abstract_popover.h"

AbstractPopover::AbstractPopover(QWidget* parent) {
    
    m_Parent = parent;
    
    m_Model      = NULL;
    m_View       = NULL;
    m_Controller = NULL;
    
    this->setLayout(new QVBoxLayout());
    
    this->layout()->setContentsMargins(0, 0, 0, 0);
}

QWidget* AbstractPopover::parent() {
    return m_Parent;
}

AbstractModel* AbstractPopover::model() {
    return m_Model;
}

AbstractView* AbstractPopover::view() {
    return m_View;
}

AbstractController* AbstractPopover::controller() {
    return m_Controller;
}
