#include <QDebug>
#include <QtAlgorithms>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>

#include "app/app_mediator.h"
#include "views/scope/scope_controller.h"
#include "views/scope/scope_view.h"

void ScopeController::on_View_Initialized(ElementManager* manager) {
    
    this->tuneTo(AppMediator::Channel::STREAM_EVENTS);
    this->tuneTo(AppMediator::Channel::STREAM_PARAMS);
    this->tuneTo(AppMediator::Channel::SCOPE_DATA);
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
void ScopeController::on_Broadcast(quint64 ch, app_data_t data) {
    
    ScopeView*  view  = (ScopeView*)this->get_View();
    
    ElementManager* manager = view->get_ElementManager();
    
    QSplineSeries* chart_series = (QSplineSeries*)manager->get("ser");
    QValueAxis*    x_axis = (QValueAxis*)manager->get("x");
    QValueAxis*    y_axis = (QValueAxis*)manager->get("y");
    
    static quint64 x = 0;
    
    static QList<QPointF> test;
    
    ////////////////////////
    
    if (ch == AppMediator::Channel::STREAM_EVENTS) {
        
        if (data.event == "new_stream") {
            
            chart_series->clear();
            
            x_axis->setRange(0, 48);
            
            x = 0;
        }
        else if (data.event == "new_sample") {
            
            test.push_back(QPointF(x, data.value.i64));
            
            x+=1;
            
            if (test.size() == 48) {
                x_axis->setRange(x - 48, x - 1);
                chart_series->replace(test);
                test.clear();
            }
        }
    }
    
    ////////////////////////
    
    else if (ch == AppMediator::Channel::SCOPE_DATA) {
        
        chart_series->clear();
        
        x_axis->setRange(data.scope_data.x_axis.first,
            data.scope_data.x_axis.second - 1);
        
         x = data.scope_data.x_axis.first;
        
        for (const auto& sample : data.scope_data.samples) {
            chart_series->append(x++, qint16(sample));
        }
    }
    
    ////////////////////////
    
    else if (ch == AppMediator::Channel::STREAM_PARAMS) {
        
        quint8 bits_per_sample = data.stream_config.bits_per_sample;
        bool   samples_signed  = data.stream_config.signed_samples;
        
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
