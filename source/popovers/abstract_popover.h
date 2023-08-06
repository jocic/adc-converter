#ifndef ADC_POPOVERS_ABSTRACT_POPOVER_H

#define ADC_POPOVERS_ABSTRACT_POPOVER_H

#include <QWidget>
#include <QDialog>

#include "mvc/abstract_model.h"
#include "mvc/abstract_view.h"
#include "mvc/abstract_controller.h"

class AbstractPopover : public QDialog {
    
    public:
        AbstractPopover(QWidget* parent = NULL);
        const QWidget* parent();
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
