#ifndef SCOPE_CHART_H
#define SCOPE_CHART_H

#include <QGestureEvent>
#include <QtCharts/QChartView>

class ScopeChartView : public QChartView {
    
    protected:
        void wheelEvent(QWheelEvent* event);
        void mousePressEvent(QMouseEvent *event);
};

#endif // SCOPE_CHART_H
