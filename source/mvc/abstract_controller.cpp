#include <QDebug>

#include "abstract_controller.h"

QWidget* AbstractController::get_Parent() {
    return m_Parent;
}

void AbstractController::set_Parent(QWidget* parent) {
    
    if (parent != NULL) {
        m_Parent = parent;
    }
}

QWidget* AbstractController::get_Widget() {
    return m_Widget;
}

void AbstractController::set_Widget(QWidget* widget) {
    
    if (widget != NULL) {
        m_Widget = widget;
    }
}

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
