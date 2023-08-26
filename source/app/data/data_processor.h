#ifndef ADC_DATA_DATA_PROCESSOR_H

#define ADC_DATA_DATA_PROCESSOR_H

#include <QObject>
#include <QTimer>
#include <QByteArray>

class DataProcessor : public QObject {
    
    Q_OBJECT
    
    protected:
        QTimer*     m_DataTimer;
        QTimer*     m_SampleTimer;
        QByteArray* m_Data;
        
    protected slots:
        virtual void on_DataTimeout() = 0;
        virtual void on_SampleTimeout() = 0;
        
    public:
        DataProcessor();
        void start();
        void stop();
        void pushData(QByteArray buffer);
        
    public slots:
        void on_NewData(QByteArray buffer);
    
    signals:
        void sig_Started();
        void sig_Stopped();
        void sig_NewSample(qint64 sample);
};

#endif
