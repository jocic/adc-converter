#ifndef ADC_WORKERS_LOAD_WORKER_H

#define ADC_WORKERS_LOAD_WORKER_H

#include <QObject>
#include <QFile>

#include "app/workers/abstract_worker.h"

class LoadWorker : public AbstractWorker {
    
    Q_OBJECT
    
    public:
        void run() override;
};

#endif
