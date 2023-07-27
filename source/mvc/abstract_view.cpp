#include "abstract_view.h"
#include "element_manager.h"

ElementManager* AbstractView::get_ElementManager() {
    
    if (m_Manager == NULL) {
        m_Manager = new ElementManager();
    }
    
    return m_Manager;
}
