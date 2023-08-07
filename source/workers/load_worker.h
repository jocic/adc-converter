#ifndef ADC_WORKERS_LOAD_WORKER_H

#define ADC_WORKERS_LOAD_WORKER_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include <QByteArray>

#include "workers/file_worker.h"

class LoadWorker : public FileWorker {
    
    Q_OBJECT
    
    private:
        quint64 get_OptimalChunkSize(QFile* file);
    
    public:
        void start(QFile* file, Priority priority = InheritPriority) override;
        void run() override;
    
    signals:
        void sig_Chunk_Read(QFile* file, QByteArray chunk);
        void sig_Error(QFile::FileError error);
};

#endif
