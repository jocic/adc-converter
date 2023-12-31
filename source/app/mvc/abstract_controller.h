#ifndef ADC_MVC_ABSTRACT_CONTROLLER_H

#define ADC_MVC_ABSTRACT_CONTROLLER_H

#include <QDebug>
#include <QObject>

#include "app/app_transceiver.h"
#include "app/mvc/abstract_model.h"
#include "app/mvc/abstract_view.h"
#include "app/mvc/element_manager.h"

class AbstractController : public AppTransceiver {
    
    Q_OBJECT
    
    private:
        QWidget*        m_Parent;
        QWidget*        m_Widget;
        AbstractModel*  m_Model;
        AbstractView*   m_View;
    
    public:
        QWidget* get_Parent();
        void set_Parent(QWidget* parent);
        QWidget* get_Widget();
        void set_Widget(QWidget* widget);
        AbstractModel* get_Model();
        void set_Model(AbstractModel* model);
        AbstractView* get_View();
        void set_View(AbstractView* view);
        void registerField(QString name, QString type);
    
    public slots:
        virtual void on_View_Initialized(ElementManager* manager) = 0;
        virtual void on_View_Changed() = 0;
        virtual void on_Model_Changed(QString key, QString value) = 0;
        virtual void on_Model_Cleared() = 0;
        
    signals:
        void sig_Controller_Connected();
        void sig_Controller_Configured();
};

#endif
