#ifndef ADC_WORKERS_ABSTRACT_FILE_WORKER_H

#define ADC_WORKERS_ABSTRACT_FILE_WORKER_H

#include <QObject>
#include <QThread>
#include <QFile>
#include <QByteArray>

class AbstractFileWorker : public QThread {
    
    Q_OBJECT
    
    protected:
        QFile* m_File;
        QByteArray* m_Buffer;
        quint64 calc_ChunkSize(quint64 size);
    
    public: 
        QFile* get_File();
        void set_File(QFile* file);
        QByteArray* get_Buffer();
        void set_Buffer(QByteArray* buffer);
        
    signals:
        void sig_Error(QFile::FileError error);
        void sig_Read(QByteArray chunk);
        void sig_Wrote(QByteArray chunk);
        void sig_Progressed(quint8 value);
        void sig_Done();
};

#endif
