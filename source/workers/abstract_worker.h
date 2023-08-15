#ifndef ADC_WORKERS_ABSTRACT_WORKER_H

#define ADC_WORKERS_ABSTRACT_WORKER_H

#include <QObject>
#include <QThread>
#include <QFile>
#include <QByteArray>

class AbstractWorker : public QThread {
    
    Q_OBJECT
    
    protected:
        QFile* m_File;
        QByteArray* m_Buffer;
    
    public:
        QFile* get_File();
        void set_File(QFile* file);
        QByteArray* get_Buffer();
        void set_Buffer(QByteArray* buffer);
};

#endif
