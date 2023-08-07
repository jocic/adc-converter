#ifndef ADC_WORKERS_FILE_WORKER_H

#define ADC_WORKERS_FILE_WORKER_H

#include <QObject>
#include <QThread>
#include <QFile>
#include <QByteArray>

class FileWorker : public QThread {
    
    Q_OBJECT
    
    protected:
        QFile* m_File;
        quint64 get_OptimalChunkSize();
    
    public:
        QFile* get_File();
        void set_File(QFile* file);
    
    signals:
        void sig_Error(QFile::FileError error);
        void sig_Read(QByteArray chunk);
        void sig_Progressed(quint8 value);
        void sig_Done();
};

#endif
