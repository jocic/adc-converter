#ifndef ADC_MVC_ABSTRACT_VIEW_H

#define ADC_MVC_ABSTRACT_VIEW_H

#include <QObject>
#include <QFrame>
#include <QWidget>
#include <QFont>
#include <QLayout>
#include <QSpacerItem>

#include "element_manager.h"

class AbstractView : public QObject {
    
    Q_OBJECT
    
    private:
        ElementManager* m_Manager;
    
    protected:
        QWidget* m_Parent;
        QFont* make_BFont();
        QFrame* make_HLine();
        QFrame* make_VLine();
        QSpacerItem* make_HSpacer();
        QSpacerItem* make_VSpacer();
    
    public:
        ElementManager* get_ElementManager();
        virtual void initialize(QWidget* parent) = 0;
        
    signals:
        void sig_View_Initialized(ElementManager* manager);
        void sig_View_Changed();
};

#endif
