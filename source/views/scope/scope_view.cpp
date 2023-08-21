#include <QDebug>
#include <QIcon>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QSlider>
#include <QPushButton>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>

#include "app/mvc/element_manager.h"
#include "views/scope/scope_view.h"

void ScopeView::initialize(QWidget* parent) {
    
    QWidget*     wd_main  = new QWidget();
    QVBoxLayout* lay_main = new QVBoxLayout();
    
    QChartView * chart_view = new QChartView();
    QChart* chart        = new QChart();
    QLineSeries* chart_series = new QLineSeries();
    QValueAxis* chart_x      = new QValueAxis();
    QValueAxis* chart_y      = new QValueAxis();
    
    chart_series->useOpenGL();
    
    chart_x->setTitleText("Time");
    chart_x->setRange(0, 128);
    
    chart_y->setTitleText("ADC Value");
    chart_y->setRange(-128, 128);
    
    chart->setBackgroundVisible(false);
    chart->addSeries(chart_series);
    chart->addAxis(chart_x, Qt::AlignmentFlag::AlignBottom);
    chart->addAxis(chart_y, Qt::AlignmentFlag::AlignLeft);
    chart->legend()->hide();
    
    chart_series->attachAxis(chart_x);
    chart_series->attachAxis(chart_y);
    
    chart_view->setChart(chart);
    chart_view->setContentsMargins(0, 0, 0, 0);
    
    lay_main->addWidget(chart_view);
    lay_main->setContentsMargins(0, 20, 0, 0);
    
    wd_main->setLayout(lay_main);
    wd_main->setStyleSheet("background: #fff");
    
    parent->layout()->addWidget(wd_main);
}
