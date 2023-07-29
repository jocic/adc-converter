#ifndef ADC_CORE_ABSTRACT_WIDGET

#define ADC_CORE_ABSTRACT_WIDGET

#include <QWidget>

#include "mvc/abstract_model.h"
#include "mvc/abstract_view.h"
#include "mvc/abstract_controller.h"

class AbstractWidget : public QWidget {
    
    public:
        AbstractWidget(QWidget* parent = NULL);
        const AbstractModel* model();
        const AbstractView* view();
        const AbstractController* controller();
        virtual void initialize() = 0;
        
    protected:
        QWidget*            m_Parent;
        AbstractModel*      m_Model;
        AbstractView*       m_View;
        AbstractController* m_Controller;
};

#endif
