#ifndef ADC_DATA_DATA_PROCESSOR_H

#define ADC_DATA_DATA_PROCESSOR_H

#include <QObject>
#include <QTimer>
#include <QByteArray>

//example
//"\n-29316.33\r\n-36061.66\r\n-42446.68"
//"\r\n-48407.58\r\n-53884.82\r\n-58823.6"
//"5\r\n-63174.74\r\n-66894.61\r\n-69946."
//"09\r\n-72298.70\r\n-73928.93\r\n-74820"
//".48\r\n-74964.44\r\n-74359.38\r\n-7301"
//"1.36\r\n-70933.83\r\n-68147.54\r\n-646"

class DataProcessor : public QObject {
    
    Q_OBJECT
    
    protected:
        QTimer*     m_Timer;
        QByteArray* m_Data;
        
    protected slots:
        virtual void on_Timeout() = 0;
        
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
};

#endif
