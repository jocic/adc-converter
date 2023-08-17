#ifndef ADC_APP_EXPORTER_H

#define ADC_APP_EXPORTER_H

#include <QFileDialog>
#include <QMutex>

#include "app/app_io.h"

class AppExporter : public AppIO {
    
    Q_OBJECT
    
    private:
        
        static AppExporter* M_INSTANCE;
        static QMutex      M_MUTEX;
        
        AppExporter();
        AppExporter(const AppExporter& ref) = delete;
        void operator = (const AppExporter& ref) = delete;
    
    public:
        static AppExporter* get_Instance();
        void process() override {};
        void process(QByteArray* buffer, quint64 sample_rate,
            quint8 bits_per_sample);
};

#endif
