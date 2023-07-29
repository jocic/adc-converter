#include <QDebug>

#include "abstract_controller.h"

ElementManager* AbstractController::get_ElementManager() {
    return m_Manager;
}

void AbstractController::set_ElementManager(ElementManager* manager) {
    
    if (manager != NULL) {
        m_Manager = manager;
    }
}
