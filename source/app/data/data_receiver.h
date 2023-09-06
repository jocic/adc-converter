#ifndef ADC_DATA_DATA_RECEIVER_H

#define ADC_DATA_DATA_RECEIVER_H

#include <QObject>
#include <QTimer>
#include <QByteArray>
#include <QtSerialPort/QSerialPort>

class DataReceiver : public QObject {
    
    Q_OBJECT
    
    private:
        
        QSerialPort* m_SerialPort;
        QTimer*      m_ReadTimer;
        QTimer*      m_SimTimer;
        
        QSerialPort::SerialPortError m_Error;
        
    private slots:
        void on_ReadInterval();
        void on_SimInterval();
        void on_ReadError(QSerialPort::SerialPortError error);
        
    public:
        DataReceiver();
        QSerialPort* serialPort();
        void start(bool simulate = false);
        void stop();
        bool isRunning();
        
    signals:
        void sig_Started();
        void sig_Stopped();
        void sig_Error();
        void sig_BufferRead(QByteArray buffer);
};

#endif
