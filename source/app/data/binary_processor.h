#ifndef ADC_DATA_BINARY_PROCESSOR_H

#define ADC_DATA_BINARY_PROCESSOR_H

#include <QObject>

#include "app/data/data_processor.h"

class BinaryProcessor : public DataProcessor {
    
    Q_OBJECT
        
    private:
        QQueue<qint32>* m_Samples;
        QByteArray* m_SampleBuffer;
        void on_DataTimeout() override;
        void on_SampleTimeout() override;
        
    public:
        BinaryProcessor();
        void start();
        void stop();
};

#endif
