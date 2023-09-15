#ifndef ADC_WORKERS_ABSTRACT_WORKER_H

#define ADC_WORKERS_ABSTRACT_WORKER_H

#include <QObject>
#include <QThread>
#include <QFile>
#include <QByteArray>

class AbstractWorker : public QThread {
    
    Q_OBJECT
        
    signals:
        void sig_Timeout();
};

#endif
