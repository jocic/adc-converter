#ifndef SCOPE_WIDGET_H
#define SCOPE_WIDGET_H

#include <QHBoxLayout>
#include <QThread>
#include <QRandomGenerator>
#include <QByteArray>
#include <QQueue>

#include <QtCore/QPointF>

#include <QtWidgets/QWidget>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>

#include "data_control.h"
#include "scope_chart.h"

class ScopeWidget : public QWidget
{
    Q_OBJECT
    
    private:
        
        QWidget*     parent;
        QHBoxLayout* layout;
    
    public:
        
        ScopeChartView* chart_view;
        
        QChart*      chart;
        QLineSeries* chart_series;
        QValueAxis*  chart_x;
        QValueAxis*  chart_y;
        
        DataControl* dat_ctl;
        
        ScopeWidget(QWidget* parent);
        
    public slots:
        
        void on_adc_resolution_change(int bits);
};

#endif // SCOPE_WIDGET_H
