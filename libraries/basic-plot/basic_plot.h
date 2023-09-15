#ifndef BASIC_PLOT_H

#define BASIC_PLOT_H

#define BORDER_WIDTH 4
#define GRID_WIDTH   1
#define SIGNAL_WIDTH 1

#include <QObject>
#include <QWidget>

class BasicPlot : public QWidget  {
    
    private:
        quint64 m_VDiv;
        quint64 m_HDiv;
        quint64 m_VDivRes;
        quint64 m_HDivRes;
        QVector<QPair<qint64, qint64>>* m_Buffer;
        QVector<QPair<qint64, qint64>>* m_BufferN;
        void paintEvent(QPaintEvent* event) override;
        void resizeEvent(QResizeEvent *event) override;;
    
    public:
        BasicPlot(QWidget* parent);
        ~BasicPlot();
        QVector<QPair<qint64, qint64>>* get_Buffer();
        void set_VDiv(quint64 div);
        quint64 get_VDiv();
        void set_HDiv(quint64 div);
        quint64 get_HDiv();
        void set_Resolution(quint64 hor, quint64 ver);
        void refresh();
};

#endif
