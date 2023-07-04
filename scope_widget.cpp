#include <QDebug>
#include <QtMath>

#include "scope_widget.h"
#include "scope_data_types.h"

ScopeWidget::ScopeWidget(QWidget* parent)
{
    // Chart Setup
    
    this->setContentsMargins(0, 0, 0, 0);
    
    this->layout       = new QHBoxLayout();
    this->chart_view   = new ScopeChartView();
    this->chart        = new QChart();
    this->chart_series = new QLineSeries();
    this->chart_x      = new QValueAxis();
    this->chart_y      = new QValueAxis();
    
    this->chart_series->useOpenGL();
    
    this->chart_x->setTitleText("Time");
    this->chart_x->setRange(0, 128);
    
    this->chart_y->setTitleText("ADC Value");
    this->chart_y->setRange(-128, 128);
    
    this->chart->setBackgroundVisible(false);
    this->chart->addSeries(this->chart_series);
    this->chart->addAxis(this->chart_x, Qt::AlignmentFlag::AlignBottom);
    this->chart->addAxis(this->chart_y, Qt::AlignmentFlag::AlignLeft);
    this->chart->legend()->hide();
    
    this->chart_series->attachAxis(this->chart_x);
    this->chart_series->attachAxis(this->chart_y);
    
    this->chart_view->setChart(this->chart);
    this->chart_view->setContentsMargins(0, 0, 0, 0);
    
    this->layout->addWidget(this->chart_view);
    
    this->setLayout(this->layout);
    
    // Horizontal/Vertical Controls
    
    chart_ref_t ref = {
        .view   = this->chart_view,
        .chart  = this->chart,
        .series = this->chart_series,
        .x_axis = this->chart_x,
        .y_axis = this->chart_y
    };
    
    this->dat_ctl = new DataControl(ref);
    
    this->dat_ctl->start();
    
}
void ScopeWidget::on_adc_resolution_change(int bits) {
    
    quint64 max = qPow(2, bits);
    
    qint64 mid = max / 2;
    
    this->chart_y->setRange(mid * -1, mid);
}
