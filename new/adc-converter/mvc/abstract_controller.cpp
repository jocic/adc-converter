#ifndef ADC_ABSTRACT_CONTROLLER

#define ADC_ABSTRACT_CONTROLLER

#include <QObject>

class AbstractController : public QObject {
    
    Q_OBJECT
    
    public:
         virtual void connectSignals();
        
    private slots:
        void on_View_Arranged();
        void on_View_Setup();
        void on_View_Reset();
        void on_View_Updated(QString name, QString reference);
        void on_Model_Updated(QString name, QString reference);
};

#endif
