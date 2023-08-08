#ifndef ADC_APP_MEDIATOR_H

#define ADC_APP_MEDIATOR_H

#include <QWidget>
#include <QObject>
#include <QMutex>
#include <QSet>
#include <QMap>
#include <QVector>

#include "mvc/abstract_controller.h"

class AppMediator : public QObject {
    
    Q_OBJECT
    
    private:
        
        static AppMediator* M_INSTANCE;
        static QMutex       M_MUTEX;
        
        QSet<const AbstractController*> m_Consumers;
        QMap<QString,QVector<const AbstractController*>> m_Subscriptions;
        
        AppMediator();
        AppMediator(const AppMediator &ref) = delete;
        void operator = (const AppMediator &ref) = delete;
        
    public:
        static AppMediator* get_Instance();
        void add_Provider(const AbstractController* ctl, QString topic);
        void add_Consumer(const AbstractController* ctl, QString topic);
        
    public slots:
        void on_Notify(QString topic, QMap<QString,QString> params);
        
    signals:
        void sig_Notify(QString topic, QMap<QString,QString> params);
};

#endif
