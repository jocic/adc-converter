#ifndef ADC_VIEWS_CUSTOM_CHART_VIEW_H

#define ADC_VIEWS_CUSTOM_CHART_VIEW_H

#include <QGestureEvent>
#include <QtCharts/QChartView>

class CustomChartView : public QChartView {
    
    protected:
        void wheelEvent(QWheelEvent* event);
        void mousePressEvent(QMouseEvent *event);
};

#endif
