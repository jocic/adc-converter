#ifndef ADC_WORKERS_EXPORT_WORKER_H

#define ADC_WORKERS_EXPORT_WORKER_H

#include <QObject>
#include <QFile>
#include <QByteArray>

#include "app/workers/abstract_worker.h"

class ExportWorker : public AbstractWorker {
    
    Q_OBJECT
    
    private:
        quint32 m_SampleRate;
        quint8  m_BitsPerSample;
        bool    m_SignedSamples;
    
    public:
        ExportWorker();
        quint32 get_SampleRate();
        void set_SampleRate(quint32 sample_rate);
        quint8 get_BitsPerSample();
        void set_BitsPerSamplee(quint8 bits_per_sample);
        bool get_SignedSamples();
        void set_SignedSamples(bool signed_samples);
        void run() override;
};

#endif
