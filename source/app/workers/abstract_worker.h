#ifndef ADC_WORKERS_ABSTRACT_WORKER_H

#define ADC_WORKERS_ABSTRACT_WORKER_H

#include <QObject>
#include <QThread>
#include <QFile>
#include <QByteArray>

class AbstractWorker : public QThread {
    
    Q_OBJECT
        
    signals:
        void sig_Error(QFile::FileError error);
        void sig_Read(QByteArray chunk);
        void sig_Wrote(QByteArray chunk);
        void sig_Progressed(quint8 value);
        void sig_Done();
};

#endif
