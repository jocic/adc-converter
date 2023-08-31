#ifndef ADC_APP_APP_TRANSCEIVER_H

#define ADC_APP_APP_TRANSCEIVER_H

#include <QObject>
#include <QVector>

#include "app/app_types.h"

class AppTransceiver : public QObject {
    
    Q_OBJECT
    
    protected:
        bool tuneTo(quint64 ch);
        
    public slots:
        virtual void on_Broadcast(quint64 ch, app_data_t data) = 0;
    
    signals:
        void sig_Broadcast(quint64 ch, app_data_t data);
};

#endif
