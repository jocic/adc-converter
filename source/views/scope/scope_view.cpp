#include <QDebug>
#include <QIcon>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QSlider>
#include <QPushButton>

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>

#include "app/mvc/element_manager.h"
#include "views/scope/scope_view.h"

void ScopeView::initialize(QWidget* parent) {
    
    QWidget*     wd_main  = new QWidget();
    QVBoxLayout* lay_main = new QVBoxLayout();
    
    QChartView *   chart_view   = new QChartView();
    QChart*        chart        = new QChart();
    QSplineSeries* chart_series = new QSplineSeries();
    QValueAxis*    chart_x      = new QValueAxis();
    QValueAxis*    chart_y      = new QValueAxis();
    
    chart_series->useOpenGL();
    
    chart_x->setTitleText("Time");
    chart_x->setRange(0, 48);
    
    chart_y->setTitleText("Voltage");
    chart_y->setRange(-32768, 32768);
    
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
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push("ser", (QWidget*)chart_series);
    manager->push("x", (QWidget*)chart_x);
    manager->push("y", (QWidget*)chart_y);
    
    emit ScopeView::sig_View_Initialized(manager);
}
