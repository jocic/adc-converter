#ifndef ADC_APP_IO_H

#define ADC_APP_IO_H

#include <QFileDialog>
#include <QMutex>
#include <QByteArray>
#include <QObject>
#include <QFile>

#include "popovers/processing/processing_popover.h"
#include "app/workers/abstract_file_worker.h"

class AppIO : public QFileDialog {
    
    Q_OBJECT
    
    private:
        QByteArray*         m_Buffer;
        ProcessingPopover*  m_Popover;
        AbstractFileWorker* m_Worker;
        
    protected:
        void set_Buffer(QByteArray* buf);
        void set_Popover(ProcessingPopover* pop);
        void set_Worker(AbstractFileWorker* wrk);
        
    protected slots:
        void on_Error(QFile::FileError error);
        void on_Abort();
        void on_Done();
        
    public:
        AppIO();
        ~AppIO();
        QByteArray* get_Buffer();
        void get_Chunk(QByteArray& buf, quint64 off, quint64 len);
        ProcessingPopover* get_Popover();
        AbstractFileWorker* get_Worker();
        bool is_Selected();
        virtual void process() = 0;
        void clear();
        
    public slots:
        void on_Write(QByteArray chunk);
        void on_Read(QByteArray& buffer, quint64 offset, quint64 length);
        
};

#endif
