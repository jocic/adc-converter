#ifndef ADC_ABSTRACT_VIEW

#define ADC_ABSTRACT_VIEW

#include <QObject>
#include <QWidget>
#include <QLayout>

class AbstractView : public QObject {
    
    Q_OBJECT
    
    protected:
        QWidget* m_Parent;
    
    public:
        virtual void initialize(QWidget* parent) = 0;
        virtual void arrange() = 0;
        
    signals:
        void sig_View_Initialized();
        void sig_View_Arranged();
};

#endif
