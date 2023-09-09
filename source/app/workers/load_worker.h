#ifndef ADC_WORKERS_LOAD_WORKER_H

#define ADC_WORKERS_LOAD_WORKER_H

#include <QObject>
#include <QFile>

#include "app/workers/abstract_file_worker.h"

class LoadWorker : public AbstractFileWorker {
    
    Q_OBJECT
    
    public:
        void run() override;
};

#endif
