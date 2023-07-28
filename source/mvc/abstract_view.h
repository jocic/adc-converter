#ifndef ADC_ABSTRACT_VIEW

#define ADC_ABSTRACT_VIEW

#include <QObject>
#include <QWidget>
#include <QLayout>

#include "element_manager.h"

class AbstractView : public QObject {
    
    Q_OBJECT
    
    private:
        ElementManager* m_Manager;
    
    protected:
        QWidget* m_Parent;
    
    public:
        ElementManager* get_ElementManager();
        virtual void initialize(QWidget* parent) = 0;
        
    signals:
        void sig_View_Initialized(ElementManager* manager);
        void sig_View_Changed();
};

#endif
