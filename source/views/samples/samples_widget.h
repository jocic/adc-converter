#ifndef ADC_VEWES_SAMPLES_WIDGET_H

#define ADC_VEWES_SAMPLES_WIDGET_H

#include "widgets/abstract_widget.h"

class SamplesWidget : public AbstractWidget {
    
    public:
        SamplesWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
