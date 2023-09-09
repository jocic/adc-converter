#ifndef ADC_WORKERS_SAVE_WORKER_H

#define ADC_WORKERS_SAVE_WORKER_H

#include <QObject>
#include <QFile>
#include <QByteArray>

#include "app/workers/abstract_file_worker.h"

class SaveWorker : public AbstractFileWorker {
    
    Q_OBJECT
    
    public:
        void run() override;
};

#endif
