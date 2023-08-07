#ifndef ADC_WORKERS_LOAD_WORKER_H

#define ADC_WORKERS_LOAD_WORKER_H

#include <QObject>

#include "workers/file_worker.h"

class LoadWorker : public FileWorker {
    
    Q_OBJECT
    
    public:
        void run() override;
};

#endif
