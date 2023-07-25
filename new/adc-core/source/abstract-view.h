#ifndef ADC_ABSTRACT_VIEW

#define ADC_ABSTRACT_VIEW

#include <QObject>

class AbstractView : public QObject {
    
    Q_OBJECT
    
    public:
         virtual void clear();
        
    signals:
        void sig_Model_Updated(QString name, QString reference);
        void sig_Model_Cleared(QString name, QString reference);
};

#endif
