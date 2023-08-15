#ifndef ADC_WORKERS_LOAD_WORKER_H

#define ADC_WORKERS_LOAD_WORKER_H

#include <QObject>
#include <QFile>

#include "workers/abstract_worker.h"

class LoadWorker : public AbstractWorker {
    
    Q_OBJECT
    
    protected:
        quint64 get_OptimalChunkSize();
    
    public:
        void run() override;
        
    signals:
        void sig_Error(QFile::FileError error);
        void sig_Read(QByteArray chunk);
        void sig_Progressed(quint8 value);
        void sig_Done();
};

#endif
