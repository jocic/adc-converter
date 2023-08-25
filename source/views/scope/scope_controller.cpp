#include <QDebug>
#include <QtAlgorithms>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>

#include "views/scope/scope_controller.h"
#include "views/scope/scope_view.h"

void ScopeController::on_View_Initialized(ElementManager* manager) {
    
    // Does nothing...
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

void ScopeController::on_Mediator_Notify(QString topic,
    QMap<QString,QString> params) {
    
    ScopeView*  view  = (ScopeView*)this->get_View();
    
    ElementManager* manager = view->get_ElementManager();
    
    QLineSeries* chart_series = (QLineSeries*)manager->get("ser");
    QValueAxis*  x_axis = (QValueAxis*)manager->get("x");
    QValueAxis*  y_axis = (QValueAxis*)manager->get("y");
    
    static quint64 x = 0;
    
    if (topic == "new_stream") {
        
        chart_series->clear();
        y_axis->setRange(-75000, 75000);
        x_axis->setRange(0, 48);
        
        x = 0;
    }
    else if (topic == "new_sample") {
        
        QString str_sample = params["value"];
        
        qint64 sample = str_sample.toLongLong();
        
        x+=1;
        qDebug() << x << sample;
        chart_series->append(x, sample);
        
        if (x > 48) {
            x_axis->setRange(x - 48, x);
            chart_series->points().removeAt(0);
        }
    }
    else if (topic == "frame_data") {
        
        chart_series->clear();
        
        y_axis->setRange(-75000, 75000);
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
}
