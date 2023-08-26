#ifndef ADC_DATA_TEXT_PROCESSOR_H

#define ADC_DATA_TEXT_PROCESSOR_H

#include <QObject>

#include "app/data/data_processor.h"

class TextProcessor : public DataProcessor {
    
    Q_OBJECT
    
    private:
        bool m_SkippedFirst;
        void on_Timeout() override;
        
    public:
        void start();
};

#endif
