#ifndef ADC_FILE_LOADER_H

#define ADC_FILE_LOADER_H

#include <QFileDialog>
#include <QMutex>

#include "popovers/processing/processing_popover.h"
#include "workers/load_worker.h"

class FileLoader : public QFileDialog {
    
    Q_OBJECT
    
    private:
        
        static FileLoader* M_INSTANCE;
        static QMutex      M_MUTEX;
        
        QByteArray*        m_Buffer;
        ProcessingPopover* m_Popover;
        LoadWorker*        m_Worker;
        
        FileLoader();
        FileLoader(const FileLoader& ref) = delete;
        void operator = (const FileLoader& ref) = delete;
    
    private slots:
        void on_Error(QFile::FileError error);
        void on_Read(QByteArray chunk);
        void on_Abort();
        void on_Done();
    
    public:
        static FileLoader* get_Instance();
        QByteArray* get_Buffer();
        QByteArray get_Chunk(quint64 off, quint64 len);
        ProcessingPopover* get_Popover();
        LoadWorker* get_Worker();
        void process();
        void clear();
};

#endif
