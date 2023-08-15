#ifndef ADC_FILE_LOADER_H

#define ADC_FILE_LOADER_H

#include <QFileDialog>
#include <QMutex>

#include "file_manager.h"

class FileLoader : public FileManager {
    
    Q_OBJECT
    
    private:
        
        static FileLoader* M_INSTANCE;
        static QMutex      M_MUTEX;
        
        FileLoader();
        FileLoader(const FileLoader& ref) = delete;
        void operator = (const FileLoader& ref) = delete;
    
    public:
        static FileLoader* get_Instance();
        void process() override;
};

#endif
