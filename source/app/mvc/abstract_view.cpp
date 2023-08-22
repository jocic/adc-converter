#include "abstract_view.h"
#include "element_manager.h"

ElementManager* AbstractView::get_ElementManager() {
    
    if (m_Manager == NULL) {
        m_Manager = new ElementManager();
    }
    
    return m_Manager;
}

QFont* AbstractView::make_BFont() {
    
    QFont* font = new QFont();
    
    font->setBold(true);
    
    return font;
}

QFrame* AbstractView::make_HLine() {
    
    QFrame* line = new QFrame();
    
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    
    return line;
}

QFrame* AbstractView::make_VLine() {
    
    QFrame* line = new QFrame();
    
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    
    return line;
}

QSpacerItem* AbstractView::make_HSpacer() {
    
    QSpacerItem* spacer = new QSpacerItem(8000, 1,
        QSizePolicy::Expanding, QSizePolicy::Minimum);
    
    return spacer;
}

QSpacerItem* AbstractView::make_VSpacer() {
    
    QSpacerItem* spacer = new QSpacerItem(1, 8000,
        QSizePolicy::Minimum, QSizePolicy::Expanding);
    
    return spacer;
}
