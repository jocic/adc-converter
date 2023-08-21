#include <QDebug>
#include <QtAlgorithms>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

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
    qDebug() << "WTF?" << topic;
    if (topic == "tab_window_data") {
        
        QLineSeries* chart_series = (QLineSeries*)manager->get("test");
        
        chart_series->clear();
        
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
            chart_series->append(point.first, point.second);
        }
        
        qDebug() << params.size();
    }
}
