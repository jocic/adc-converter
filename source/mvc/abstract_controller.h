#ifndef ADC_ABSTRACT_CONTROLLER

#define ADC_ABSTRACT_CONTROLLER

#include <QObject>

#include "element_manager.h"

class AbstractController : public QObject {
    
    Q_OBJECT
    
    public:
//         virtual void connect();
//         virtual void configure();
        
//    private slots:
//        void on_View_Arranged();
//        void on_View_Setup();
//        void on_View_Reset();
//        void on_View_Updated();
//        void on_Model_Updated();
//        void on_Model_Cleared();
    
    public slots:
        void on_View_Initialized(ElementManager* manager);
        void on_View_Changed();
        void on_Model_Changed(QString key, QString value);
        void on_Model_Cleared();
        
    signals:
        void sig_Controller_Connected();
        void sig_Controller_Configured();
};

#endif
