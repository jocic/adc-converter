#ifndef ADC_DATA_BINARY_PROCESSOR_H

#define ADC_DATA_BINARY_PROCESSOR_H

#include <QObject>

#include "app/data/data_processor.h"

class BinaryProcessor : public DataProcessor {
    
    Q_OBJECT
        
    private:
        QQueue<qint32>* m_Samples;
        quint8 m_BitsPerSample;
        qint32 m_SampleBuffer;
        quint8 m_BitsCount;
        bool m_BigEndian;
        void on_DataTimeout() override;
        void on_SampleTimeout() override;
        
    public:
        BinaryProcessor();
        void start(quint8 bits_per_sample, bool big_endian = true);
        void stop();
};

#endif
