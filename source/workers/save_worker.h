#ifndef ADC_WORKERS_SAVE_WORKER_H

#define ADC_WORKERS_SAVE_WORKER_H

#include <QObject>
#include <QFile>
#include <QByteArray>

#include "workers/abstract_worker.h"

class SaveWorker : public AbstractWorker {
    
    Q_OBJECT
    
    public:
        void run() override;
};

#endif
