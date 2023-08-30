#include <QDebug>
#include <QtAlgorithms>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>

#include "views/scope/scope_controller.h"
#include "views/scope/scope_view.h"

void ScopeController::on_View_Initialized(ElementManager* manager) {
    
    this->tuneTo("new_stream");
    this->tuneTo("new_sample");
    this->tuneTo("frame_data");
    this->tuneTo("wd_stream_data");
}

void ScopeController::on_View_Changed() {
    
    // Does nothing...
}

void ScopeController::on_Model_Changed(QString key, QString value) {
    
    // Does nothing...
}

void ScopeController::on_Model_Cleared() {
    
    // Does nothing...
}
#include <QList>
#include <QPointF>
void ScopeController::on_Broadcast(QString topic,
    QMap<QString,QString> params) {
    
    ScopeView*  view  = (ScopeView*)this->get_View();
    
    ElementManager* manager = view->get_ElementManager();
    
    QSplineSeries* chart_series = (QSplineSeries*)manager->get("ser");
    QValueAxis*    x_axis = (QValueAxis*)manager->get("x");
    QValueAxis*    y_axis = (QValueAxis*)manager->get("y");
    
    static quint64 x = 0;
    
    static QList<QPointF> test;
    
    if (topic == "new_stream") {
        
        chart_series->clear();
        
        x_axis->setRange(0, 48);
        
        x = 0;
    }
    else if (topic == "new_sample") {
        
        QString str_sample = params["value"];
        
        qint64 sample = str_sample.toLongLong();
        
        test.push_back(QPointF(x, sample));
        
        x+=1;
        
        if (test.size() == 49) {
            x_axis->setRange(x - 48, x);
            chart_series->replace(test);
            test.clear();
        }
    }
    else if (topic == "frame_data") {
        
        chart_series->clear();
        
        x_axis->setRange(0, params.size() - 1);
        
        QVector<QPair<quint64, quint64>> data;
        
        for (auto i = params.cbegin(); i != params.cend(); i++) {
            
            quint64 x = i.key().toULongLong();
            quint64 y = i.value().toULongLong();
            
            data.push_back({ x, y });
        }
        
        for (int i = 0; i < data.size(); i++) {
            for (int j = i + 1; j < data.size(); j++) {
                
                if (data[j].first <= data[i].first) {
                    qSwap(data[i], data[j]);
                }
            }
        }
        
        for (const auto& point : data) {
            chart_series->append(point.first, qint16(point.second));
        }
        
        qDebug() << params.size();
    }
    else if (topic == "wd_stream_data") {
        
        quint8 bits_per_sample = 16;
        bool   samples_signed  = true;
        
        if (params.contains("comb_BitsPerSample")) {
            bits_per_sample = params["comb_BitsPerSample"].toUInt();
        }
        
        if (params.contains("check_Signed")) {
            samples_signed = (params["check_Signed"] == "true");
        }
        
        qint64 min_range = 0, max_range = 0;
        
        if (samples_signed) {
            max_range = pow(2, bits_per_sample - 1);
            min_range = max_range * -1;
        } else {
            max_range = pow(2, bits_per_sample);
            min_range = 0;
        }
        
        y_axis->setRange(min_range, max_range);
    }
}
