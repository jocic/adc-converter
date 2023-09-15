#include <QDebug>
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QPainterPath>
#include <QPen>

#include "basic_plot.h"

BasicPlot::BasicPlot(QWidget* parent) {
    
    m_Buffer  = new QVector<QPair<qint64, qint64>>();
    m_BufferN = new QVector<QPair<qint64, qint64>>();
    
    m_HDiv = 4;
    m_VDiv = 4;
    
    m_HDivRes = 1000;
    m_VDivRes = 1000;
    
    this->setMinimumWidth(480);
    this->setMinimumHeight(480);
}

BasicPlot::~BasicPlot() {
    
    delete m_Buffer;
}

QVector<QPair<qint64, qint64>>* BasicPlot::get_Buffer() {
    return m_Buffer;
}

void BasicPlot::set_VDiv(quint64 div) {
    
    if (div > 0) {
        m_VDiv = div;
    }
    
    this->refresh();
}

quint64 BasicPlot::get_VDiv() {
    return m_VDiv;
}

void BasicPlot::set_HDiv(quint64 div) {
    
    if (div > 0) {
        m_HDiv = div;
    }
    
    this->refresh();
}

quint64 BasicPlot::get_HDiv() {
    return m_HDiv;
}


void BasicPlot::set_Resolution(quint64 hor, quint64 ver) {
    
    if (hor == 0 || ver == 0) {
        return;
    }
    
    m_HDivRes = hor;
    m_VDivRes = ver;
    
    this->refresh();
}

void BasicPlot::refresh() {
    
    quint64 width  = this->width();
    quint64 height = this->height();
    
    m_BufferN->clear();
    
    for (const auto& p : *m_Buffer) {
        
        QPair<qint64, qint64> pn;
        
        pn.first = ((p.first * (width - BORDER_WIDTH * 2)) /
            (m_VDiv * m_VDivRes)) + BORDER_WIDTH;
        
        pn.second = height - (((p.second * (height - BORDER_WIDTH * 2)) /
            (m_HDiv * m_HDivRes)) + BORDER_WIDTH);
        
        m_BufferN->append(pn);
    }
    
    this->repaint();
}

void BasicPlot::paintEvent(QPaintEvent* event) {
    
    QPainter painter(this);
    
    quint64 width  = this->width();
    quint64 height = this->height();
    
    ///////////////////////
    
    QBrush brush_bg;
    
    brush_bg.setColor(QColor(255, 255, 255));
    brush_bg.setStyle(Qt::BrushStyle::SolidPattern);
    
    ///////////////////////
    
    QPen pen_border;
    
    pen_border.setWidth(BORDER_WIDTH);
    pen_border.setColor(QColor(200, 200, 200));
    
    QPen pen_grid;
    
    pen_grid.setWidth(GRID_WIDTH);
    pen_grid.setColor(QColor(200, 200, 200));
    
    QPen pen_signal;
    
    pen_signal.setWidth(SIGNAL_WIDTH);
    pen_signal.setColor(QColor(200, 0, 0));
    
    ///////////////////////
    
    painter.fillRect(0, 0, width, height, brush_bg);
    
    ///////////////////////
    
    quint64 v_step = width / m_VDiv;
    
    for (quint64 i = 0; i < m_HDiv; i++) {
        painter.setPen(pen_grid);
        painter.drawLine(v_step * i, 0, v_step * i, height);
    }
    
    ///////////////////////
    
    quint64 h_step = height / m_HDiv;
    
    for (quint64 i = 0; i < m_VDiv; i++) {
        painter.setPen(pen_grid);
        painter.drawLine(0, h_step * i, width, h_step * i);
    }
    
    ///////////////////////
    
    painter.setPen(pen_signal);
    
    for (quint64 i = 1; i < m_BufferN->size(); i++) {
        
        painter.drawLine(
            m_BufferN->at(i - 1).first,
            m_BufferN->at(i - 1).second,
            m_BufferN->at(i).first,
            m_BufferN->at(i).second);
    }
    ///////////////////////
    
    painter.setPen(pen_border);
    painter.drawRect(pen_border.width() / 2,
        pen_border.width() / 2,
        width - pen_border.width(),
        height - pen_border.width()
    );
}

void BasicPlot::resizeEvent(QResizeEvent *event) {
    this->refresh();
}
