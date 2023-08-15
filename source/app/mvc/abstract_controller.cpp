#include <QDebug>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>

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

void AbstractController::registerField(QString name, QString type) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    qDebug() << "Registering field:" << name << type;
    
    if (type == "QLineEdit") {
        QLineEdit* field = (QLineEdit*)manager->get(name);    
        connect(field, &QLineEdit::textChanged,
            this, &AbstractController::on_View_Changed);
    } else if (type == "QComboBox") {
        QComboBox* field = (QComboBox*)manager->get(name);    
        connect(field, &QComboBox::currentIndexChanged,
            this, &AbstractController::on_View_Changed);
    } else if (type == "QCheckBox") {
        QCheckBox* field = (QCheckBox*)manager->get(name);    
        connect(field, &QCheckBox::stateChanged,
            this, &AbstractController::on_View_Changed);
    } else {
        qDebug() << "Field type not supported...";
    }
}
