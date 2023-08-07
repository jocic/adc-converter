#ifndef ADC_WORKERS_FILE_WORKER_H

#define ADC_WORKERS_FILE_WORKER_H

#include <QObject>
#include <QThread>
#include <QFile>

class FileWorker : public QThread {
    
    Q_OBJECT
    
    protected:
        QFile* m_File;
    
    public:
        virtual void start(QFile* file, Priority priority = InheritPriority) = 0;
};

#endif
