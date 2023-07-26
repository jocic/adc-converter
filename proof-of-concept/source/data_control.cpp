#include <QDebug>
#include <QMutex>

#include "data_control.h"

DataControl::DataControl(chart_ref_t ref)
{
    this->chart_ref  = ref;
    this->data_raw   = new QQueue<QByteArray>();
    this->data       = new QQueue<qint64>();
    
    this->configure(10);
}

void DataControl::configure(quint64 queue_delay_ms)
{
    this->queue_delay_ms = queue_delay_ms;
}

void DataControl::run()
{
    quint64  x      = 0;
    bool processing = false;
    
    QQueue<qint64> window;
    
    while (true) {
        
        while (!window.empty()) {
            
            qint64 sample_value = window.front();
            window.pop_front();
            
            emit this->point_processed(sample_value);
            
            this->chart_ref.series->append(x++, sample_value);
            
            if (this->chart_ref.series->points().size() > 256) {
                
                this->chart_ref.series->removePoints(0, 128);
                
                QPointF front = this->chart_ref.series->points().front();
                
                this->chart_ref.x_axis->setRange(front.x(), front.x() + 128);
            }
            
            qDebug() << "Series Size: " << this->chart_ref.series->points().size();
        }
        
        if (!this->data_raw->empty()) {
            
            QByteArray bytes = this->data_raw->front();
            this->data_raw->pop_front(); 
            
            qint64  sample_value = 0;
            quint64 array_length = bytes.size() - 1;
            
            if (this->mode == 0) {
                
                bool skipped_first = false;
                
                for (quint64 i = 0; i < array_length; i++) {
                    
                    if (   (bytes[i] == '\r' && bytes[i + 1] == '\n')
                        || (bytes[i] == '\n' && bytes[i + 1] == '\r')) {
                        
                        if (skipped_first) {
                            window.push_back(sample_value);
                        }
                        
                        sample_value  = 0;
                        skipped_first = true;
                    }
                    
                    if (!skipped_first) {
                        continue;
                    }
                    
                    if (bytes[i] >= '0' && bytes[i] <= '9') {
                        sample_value *= 10;
                        sample_value += bytes[i] - '0';
                    }
                }
            }
            else {
                
                for (quint64 i = 1; i < array_length && y > 0; i+=2) {
                    sample_value = (bytes[i] & 0xFF) | ((bytes[i - 1] << 8) & 0xFF);
                }
                this->msleep(100);
            }
            
            y++;
        }
    }
}

void DataControl::on_new_data(QByteArray data) {
    
    *this->data_raw += data;
}
