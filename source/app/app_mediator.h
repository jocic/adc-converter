#ifndef ADC_APP_MEDIATOR_H

#define ADC_APP_MEDIATOR_H

#include <QWidget>
#include <QObject>
#include <QMutex>
#include <QSet>
#include <QMap>
#include <QVector>

#include "app/app_transceiver.h"

class AppMediator : public QObject {
    
    Q_OBJECT
    
    private:
        
        static AppMediator* M_INSTANCE;
        static QMutex       M_MUTEX;
        
        QSet<const AppTransceiver*> m_Providers;
        QSet<const AppTransceiver*> m_Consumers;
        QMap<QString,QVector<const AppTransceiver*>> m_Subscriptions;
        
        AppMediator();
        AppMediator(const AppMediator &ref) = delete;
        void operator = (const AppMediator &ref) = delete;
        
    public:
        static AppMediator* get_Instance();
        void reg_Transmitter(const AppTransceiver* ctl, QString topic);
        void reg_Receiver(const AppTransceiver* ctl, QString topic);
        
    public slots:
        void on_Broadcast(QString topic, QMap<QString,QString> params);
        void on_Broadcast_ALT(QString topic, void* params);
        
    signals:
        void sig_Broadcast(QString topic, QMap<QString,QString> params);
        void sig_Broadcast_ALT(QString topic, void* params);
};

#endif
