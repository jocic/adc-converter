#include <QDebug>
#include <QtCharts/QValueAxis>

#include "custom_chart_view.h"

void CustomChartView::wheelEvent(QWheelEvent* event) {
    
    QPoint angle = event->angleDelta();
    
    QValueAxis* y_axis = (QValueAxis*)this->chart()->axes().back();
    
    int min = y_axis->min();
    int max = y_axis->max();
    
    int delta = (max - min) * 0.25F;
    
    if (delta < 50) {
        delta = 50;
    }
    
    if (angle.y() > 0) {
        y_axis->setRange(min - delta, max - delta);
    } else {
        y_axis->setRange(min + delta, max + delta);
    }
}

void CustomChartView::mousePressEvent(QMouseEvent *event) {
    
    Qt::MouseButton button_pressed = event->button();
    
    QValueAxis* y_axis = (QValueAxis*)this->chart()->axes().back();
    
    qint64 min = y_axis->min();
    qint64 max = y_axis->max();
    
    qint64 delta = (max - min) * 0.25F;
    
    if (delta < 50) {
        delta = 50;
    }
    
    if (button_pressed == Qt::MouseButton::LeftButton) {
        qDebug() << "Zooming in...";
        y_axis->setRange(min + delta, max - delta);
    }
    else if (button_pressed == Qt::MouseButton::RightButton) {
        qDebug() << "Zooming in...";   
        y_axis->setRange(min - delta, max + delta);
    }
}
