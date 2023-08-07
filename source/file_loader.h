#ifndef ADC_FILE_LOADER_H

#define ADC_FILE_LOADER_H

#include <QFileDialog>
#include <QFile>

#include "popovers/processing/processing_popover.h"
#include "workers/load_worker.h"

class FileLoader : public QFileDialog {
    
    Q_OBJECT
    
    private:
        ProcessingPopover* m_Popover;
        LoadWorker*        m_Worker;
        QFile*             m_Current;
        quint64            m_Loaded;
    
    private slots:
        void on_Read_Error(LoadWorker::ErrorFlags error);
        void on_Chunk_Read(QFile* file, QByteArray chunk);
    
    public:
        FileLoader();
        void process();
    
    signals:
        void sig_Progress_Resize(int minimum, int maximum);
        void sig_Progress_Update(int value);
};

#endif
