#ifndef ADC_ABSTRACT_CONTROLLER

#define ADC_ABSTRACT_CONTROLLER

#include <QObject>

#include "element_manager.h"

class AbstractController : public QObject {
    
    Q_OBJECT
    
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
