#ifndef ADC_WORKERS_EXPORT_WORKER_H

#define ADC_WORKERS_EXPORT_WORKER_H

#include <QObject>
#include <QFile>
#include <QByteArray>

#include "app/workers/abstract_file_worker.h"

class ExportWorker : public AbstractFileWorker {
    
    Q_OBJECT
    
    private:
        quint32 m_SampleRate;
        quint8  m_BitsPerSample;
    
    public:
        ExportWorker();
        quint32 get_SampleRate();
        void set_SampleRate(quint32 sample_rate);
        quint8 get_BitsPerSample();
        void set_BitsPerSamplee(quint8 bits_per_sample);
        void run() override;
};

#endif
