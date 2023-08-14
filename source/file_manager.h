#ifndef ADC_FILE_MANAGER_H

#define ADC_FILE_MANAGER_H

#include <QFileDialog>
#include <QMutex>
#include <QByteArray>
#include <QFile>

#include "popovers/processing/processing_popover.h"
#include "workers/file_worker.h"

class FileManager : public QFileDialog {
    
    Q_OBJECT
    
    private:
        QByteArray*        m_Buffer;
        ProcessingPopover* m_Popover;
        FileWorker*        m_Worker;
        
    private slots:
        void on_Error(QFile::FileError error);
        void on_Abort();
        void on_Done();
        
    protected:
        void set_Buffer(QByteArray* buf);
        void set_Popover(ProcessingPopover* pop);
        void set_Worker(FileWorker* wrk);
        
    public:
        FileManager();
        ~FileManager();
        QByteArray* get_Buffer();
        void get_Chunk(QByteArray& buf, quint64 off, quint64 len);
        ProcessingPopover* get_Popover();
        FileWorker* get_Worker();
        bool is_Selected();
        virtual void process() = 0;
        void clear();
        
    public slots:
        void on_Write(QByteArray chunk);
        void on_Read(QByteArray& buffer, quint64 offset, quint64 length);
        
};

#endif
