#ifndef ADC_WIDGETS_ABSTRACT_WIDGET_H

#define ADC_WIDGETS_ABSTRACT_WIDGET_H

#include <QWidget>

#include "mvc/abstract_model.h"
#include "mvc/abstract_view.h"
#include "mvc/abstract_controller.h"

class AbstractWidget : public QWidget {
    
    public:
        AbstractWidget(QWidget* parent = NULL);
        QWidget* parent();
        AbstractModel* model();
        AbstractView* view();
        AbstractController* controller();
        virtual void initialize() = 0;
        
    protected:
        QWidget*            m_Parent;
        AbstractModel*      m_Model;
        AbstractView*       m_View;
        AbstractController* m_Controller;
};

#endif
