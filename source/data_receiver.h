#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <QThread>
#include <QSerialPort>
#include <QtCore/QList>
#include <QtCore/QPointF>
#include <QtCore/QQueue>

class DataReceiver : public QThread
{
    Q_OBJECT
    
    private:
        QSerialPort* serial_port;
        quint64      sample_rate;
        quint8       bits_per_sample;
        quint8       bytes_per_sample;
        bool         signed_sample;
    
    public:
        DataReceiver();
        bool configure(QString port_name, quint32 baud_rate);
        void setSampleRate(quint64 sample_rate);
        void setBitsPerSample(quint8 bits_per_sample, bool signed_sample);
        void run();
        
    signals:
        void new_data(QByteArray data);
};

#endif // DATARECEIVER_H
