#ifndef ADC_WORKERS_SAVE_WORKER_H

#define ADC_WORKERS_SAVE_WORKER_H

#include <QObject>
#include <QFile>
#include <QByteArray>

#include "workers/abstract_worker.h"

class SaveWorker : public AbstractWorker {
    
    Q_OBJECT
    
    protected:
        quint64 get_OptimalChunkSize();
    
    public:
        void run() override;
        
    signals:
        void sig_Error(QFile::FileError error);
        void sig_Wrote(QByteArray chunk);
        void sig_Progressed(quint8 value);
        void sig_Done();
};

#endif
