#ifndef ADC_APP_APP_TRANSCEIVER_H

#define ADC_APP_APP_TRANSCEIVER_H

#include <QObject>
#include <QVector>

class AppTransceiver : public QObject {
    
    Q_OBJECT
    
    protected:
        bool tuneTo(QString channel);
        
    public slots:
        virtual void on_Broadcast(QString topic, QMap<QString,QString> params) = 0;
        virtual void on_Broadcast_ALT(QString topic, void* params) = 0;
    
    signals:
        void sig_Broadcast(QString topic, QMap<QString,QString> params);
        void sig_Broadcast_ALT(QString topic, void* params);
};

#endif
