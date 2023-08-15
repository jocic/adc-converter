#ifndef ADC_POPOVERS_ABSTRACT_POPOVER_H

#define ADC_POPOVERS_ABSTRACT_POPOVER_H

#include <QWidget>
#include <QDialog>

#include "app/mvc/abstract_model.h"
#include "app/mvc/abstract_view.h"
#include "app/mvc/abstract_controller.h"

class AbstractPopover : public QDialog {
    
    public:
        AbstractPopover(QWidget* parent = NULL);
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
