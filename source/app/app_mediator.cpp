#include <QMutexLocker>

#include "app/app_mediator.h"

AppMediator* AppMediator::M_INSTANCE = NULL;
QMutex       AppMediator::M_MUTEX;

AppMediator* AppMediator::get_Instance() {
    
    QMutexLocker lock(&M_MUTEX);
    
    if (M_INSTANCE == NULL) {
        M_INSTANCE = new AppMediator();
    }
    
    return M_INSTANCE;
}

AppMediator::AppMediator() {
    
    // Does nothing...
}

void AppMediator::reg_Transmitter(const AppTransceiver* ctl, quint64 ch) {
    
    //qDebug() << "Adding provider for topic:" << topic;
    
    if (!m_Providers.contains(ctl)) {
        
        //qDebug() << "Registering provider reference...";
        
        m_Providers.insert(ctl);
        
        connect(ctl, &AppTransceiver::sig_Broadcast,
            this, &AppMediator::on_Broadcast);
    }
}

void AppMediator::reg_Receiver(const AppTransceiver* ctl, quint64 ch) {
    
    //qDebug() << "Attempting to add a consumer...";
    
    if (ctl != NULL) {
        
        //qDebug() << "Registering to topic...";
        
        m_Subscriptions[ch].push_back(ctl);
        
        if (!m_Consumers.contains(ctl)) {
            
            //qDebug() << "Registering consumer reference...";
            
            m_Consumers.insert(ctl);
            
            connect(this, &AppMediator::sig_Broadcast,
                ctl, &AppTransceiver::on_Broadcast);
        }
    }
}

void AppMediator::on_Broadcast(quint64 ch, app_data_t data) {
    
    auto search = m_Subscriptions.find(ch);
    
    //qDebug() << "Notification received: (topic, params)" << topic << params;
    
    emit AppMediator::sig_Broadcast(ch, data);
}
