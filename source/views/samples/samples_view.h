#ifndef ADC_VEWS_SAMPLES_VIEW_H

#define ADC_VEWS_SAMPLES_VIEW_H

#include <QWidget>
#include <QLabel>
#include <QVector>

#include "mvc/abstract_view.h"

class SamplesView : public AbstractView {
    
    Q_OBJECT
    
    public:
        void initialize(QWidget* parent) override;
        QVector<QLabel*>* test();
    
    private:
        QWidget* make_Overview();
        QWidget* make_Table();
        QWidget* make_Navigator();
        QWidget* make_Offseter();
};

#endif
