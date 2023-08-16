#ifndef ADC_APP_LOADER_H

#define ADC_APP_LOADER_H

#include <QFileDialog>
#include <QMutex>

#include "app/app_io.h"

class AppLoader : public AppIO {
    
    Q_OBJECT
    
    private:
        
        static AppLoader* M_INSTANCE;
        static QMutex      M_MUTEX;
        
        AppLoader();
        AppLoader(const AppLoader& ref) = delete;
        void operator = (const AppLoader& ref) = delete;
    
    public:
        static AppLoader* get_Instance();
        void process() override;
};

#endif
