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

void AppMediator::reg_Transmitter(const AppTransceiver* ctl, QString topic) {
    
    //qDebug() << "Adding provider for topic:" << topic;
    
    if (!m_Providers.contains(ctl)) {
        
        //qDebug() << "Registering provider reference...";
        
        m_Providers.insert(ctl);
        
        connect(ctl, &AppTransceiver::sig_Broadcast,
            this, &AppMediator::on_Broadcast);
        
        connect(ctl, &AppTransceiver::sig_Broadcast_ALT,
            this, &AppMediator::on_Broadcast_ALT);
    }
}

void AppMediator::reg_Receiver(const AppTransceiver* ctl, QString topic) {
    
    //qDebug() << "Attempting to add a consumer...";
    
    if (ctl != NULL) {
        
        //qDebug() << "Registering to topic...";
        
        m_Subscriptions[topic].push_back(ctl);
        
        if (!m_Consumers.contains(ctl)) {
            
            //qDebug() << "Registering consumer reference...";
            
            m_Consumers.insert(ctl);
            
            connect(this, &AppMediator::sig_Broadcast,
                ctl, &AppTransceiver::on_Broadcast);
            
            connect(this, &AppMediator::sig_Broadcast_ALT,
                ctl, &AppTransceiver::on_Broadcast_ALT);
        }
    }
}

void AppMediator::on_Broadcast(QString topic, QMap<QString,QString> params) {
    
    auto search = m_Subscriptions.find(topic);
    
    //qDebug() << "Notification received: (topic, params)" << topic << params;
    
    emit AppMediator::sig_Broadcast(topic, params);
}

void AppMediator::on_Broadcast_ALT(QString topic, void* params) {
    
    auto search = m_Subscriptions.find(topic);
    
    //qDebug() << "Notification received: (topic, params)" << topic << params;
    
    emit AppMediator::sig_Broadcast_ALT(topic, params);
}
