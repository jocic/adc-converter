#ifndef ADC_OPTIONS_SMP_WIDGET

#define ADC_OPTIONS_SMP_WIDGET

#include "widgets/abstract_widget.h"

class SmpWidget : public AbstractWidget {
    
    public:
        SmpWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
