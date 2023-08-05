#include <QDebug>

#include "abstract_controller.h"

AbstractModel* AbstractController::get_Model() {
    return m_Model;
}

void AbstractController::set_Model(AbstractModel* model) {
    
    if (model != NULL) {
        m_Model = model;
    }
}

AbstractView* AbstractController::get_View() {
    return m_View;
}

void AbstractController::set_View(AbstractView* view) {
    
    if (view != NULL) {
        m_View = view;
    }
}
