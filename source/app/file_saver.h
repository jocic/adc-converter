#ifndef ADC_FILE_SAVER_H

#define ADC_FILE_SAVER_H

#include <QFileDialog>
#include <QMutex>

#include "file_manager.h"

class FileSaver : public FileManager {
    
    Q_OBJECT
    
    private:
        
        static FileSaver* M_INSTANCE;
        static QMutex      M_MUTEX;
        
        FileSaver();
        FileSaver(const FileSaver& ref) = delete;
        void operator = (const FileSaver& ref) = delete;
    
    public:
        static FileSaver* get_Instance();
        void process() override {};
        void process(QByteArray* buffer);
};

#endif
