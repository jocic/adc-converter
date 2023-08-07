#ifndef ADC_WORKERS_LOAD_WORKER_H

#define ADC_WORKERS_LOAD_WORKER_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include <QByteArray>

#include "workers/file_worker.h"

class LoadWorker : public FileWorker {
    
    Q_OBJECT
    
    public:
        
        enum ErrorFlags {
            ERR_NONE = 0,
            ERR_OPEN = 1
        };
        
        Q_ENUM(ErrorFlags);
        
        void start(QFile* file, Priority priority = InheritPriority) override;
        void stop() override;
        void pause() override;
        void run() override;
    
    signals:
        void sig_Chunk_Read(QFile* file, QByteArray chunk);
        void sig_Error(ErrorFlags flag);
};

#endif
