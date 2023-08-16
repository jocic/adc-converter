#ifndef ADC_APP_SAVER_H

#define ADC_APP_SAVER_H

#include <QFileDialog>
#include <QMutex>

#include "app/app_io.h"

class AppSaver : public AppIO {
    
    Q_OBJECT
    
    private:
        
        static AppSaver* M_INSTANCE;
        static QMutex      M_MUTEX;
        
        AppSaver();
        AppSaver(const AppSaver& ref) = delete;
        void operator = (const AppSaver& ref) = delete;
    
    public:
        static AppSaver* get_Instance();
        void process() override {};
        void process(QByteArray* buffer);
};

#endif
