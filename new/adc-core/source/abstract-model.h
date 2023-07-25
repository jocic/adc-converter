#ifndef ADC_ABSTRACT_MODEL

#define ADC_ABSTRACT_MODEL

#include <QObject>

class AbstractModel : public QObject {
    
    Q_OBJECT
    
    public:
         void* get_ElementManager();
         virtual void arrange();
         virtual void setup();
         virtual void reset();
        
    signals:
        void sig_View_Arranged();
        void sig_View_Setup();
        void sig_View_Reset();
        void sig_View_Updated();
};

#endif
