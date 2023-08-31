#ifndef ADC_APP_MEDIATOR_H

#define ADC_APP_MEDIATOR_H

#include <QWidget>
#include <QObject>
#include <QMutex>
#include <QSet>
#include <QMap>
#include <QVector>

#include "app/app_transceiver.h"
#include "app/app_types.h"

class AppMediator : public QObject {
    
    Q_OBJECT
        
    public:
        
        enum Channel {
            
            /**
             *
             */
            APP_EVENTS,
            
            /**
             *
             */
            APP_REQUESTS,
            
            /**
             * stream_started, stream_ended, new_stream
             */
            STREAM_EVENTS,
            
            /**
             *
             */
            STREAM_PARAMS,
            REFERENCE_PARAMS,
            SERIAL_PARAMS,
            COMM_PARAMS,
            
            /**
             *
             */
            SCOPE_DATA
        };
        
        Q_ENUM(Channel);
        
        static AppMediator* get_Instance();
        void reg_Transmitter(const AppTransceiver* ctl, quint64 ch);
        void reg_Receiver(const AppTransceiver* ctl, quint64 ch);
        
    public slots:
        void on_Broadcast(quint64 ch, app_data_t data);
        
    private:
        
        static AppMediator* M_INSTANCE;
        static QMutex       M_MUTEX;
        
        QSet<const AppTransceiver*> m_Providers;
        QSet<const AppTransceiver*> m_Consumers;
        QMap<quint64,QVector<const AppTransceiver*>> m_Subscriptions;
        
        AppMediator();
        AppMediator(const AppMediator &ref) = delete;
        void operator = (const AppMediator &ref) = delete;
        
    signals:
        void sig_Broadcast(quint64 ch, app_data_t data);
};

#endif
