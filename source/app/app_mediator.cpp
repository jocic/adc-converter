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

void AppMediator::add_Provider(const AbstractController* ctl, QString topic) {
    
    qDebug() << "Adding provider for topic:" << topic;
    
    if (!m_Providers.contains(ctl)) {
        
        qDebug() << "Registering provider reference...";
        
        m_Providers.insert(ctl);
        
        connect(ctl, &AbstractController::sig_Mediator_Notify,
            this, &AppMediator::on_Notify);
    }
}

void AppMediator::add_Consumer(const AbstractController* ctl, QString topic) {
    
    qDebug() << "Attempting to add a consumer...";
    
    if (ctl != NULL) {
        
        qDebug() << "Registering to topic...";
        
        m_Subscriptions[topic].push_back(ctl);
        
        if (!m_Consumers.contains(ctl)) {
            
            qDebug() << "Registering consumer reference...";
            
            m_Consumers.insert(ctl);
            
            connect(this, &AppMediator::sig_Notify,
                ctl, &AbstractController::on_Mediator_Notify);
        }
    }
}

void AppMediator::on_Notify(QString topic, QMap<QString,QString> params) {
    
    auto search = m_Subscriptions.find(topic);
    
    if (search != m_Subscriptions.end()) {
        
        for (const auto ctl : *search) {
            emit AppMediator::sig_Notify(topic, params);
        }
    }
}
