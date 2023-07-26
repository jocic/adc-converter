#ifndef ADC_ABSTRACT_VIEW

#define ADC_ABSTRACT_VIEW

#include <QObject>

class AbstractView : public QObject {
    
    Q_OBJECT
    
    public:
         void clear();
        
    signals:
        void sig_Model_Updated();
        void sig_Model_Cleared();
};

#endif
