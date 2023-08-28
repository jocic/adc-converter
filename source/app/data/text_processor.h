#ifndef ADC_DATA_TEXT_PROCESSOR_H

#define ADC_DATA_TEXT_PROCESSOR_H

#include <QObject>
#include <QQueue>
#include "app/data/data_processor.h"

class TextProcessor : public DataProcessor {
    
    Q_OBJECT
    
    private:
        QQueue<QString>* m_Samples;
        QString m_SampleBuffer;
        bool m_SkippedFirst;
        void on_DataTimeout() override;
        void on_SampleTimeout() override;
        
    public:
        TextProcessor();
        void start();
        void stop();
};

#endif
