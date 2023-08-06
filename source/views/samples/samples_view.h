#ifndef ADC_VEWS_SAMPLES_VIEW_H

#define ADC_VEWS_SAMPLES_VIEW_H

#include <QWidget>

#include "mvc/abstract_view.h"

class SamplesView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
    
    private:
        QWidget* make_Overview();
        QWidget* make_Navigator();
        QWidget* make_Offseter();
};

#endif
