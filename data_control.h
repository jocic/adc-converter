#ifndef DATACONTROL_H
#define DATACONTROL_H

#include <QThread>
#include <QQueue>
#include <QByteArray>
#include <QPointF>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include "scope_data_types.h"

class DataControl : public QThread
{
    Q_OBJECT
    
    private:
        chart_ref_t         chart_ref;
        quint64             queue_delay_ms;
    
    public:
        quint8              mode;
        quint64 _x = 0, x = 0;
        quint64  y      = 0;
        QQueue<qint64>*     data;
        QQueue<QByteArray>* data_raw;
        DataControl(chart_ref_t ref);
        void configure(quint64 queue_delay_ms);
        // associate chart view
        // associate chart series
        void run();
        void reset() {
            
            _x = 0; x = 0; y = 0;
        }
        
    public slots:
        void on_new_data(QByteArray data);
    
    signals:
        void point_processed(qint64 point);
};

#endif // DATACONTROL_H
