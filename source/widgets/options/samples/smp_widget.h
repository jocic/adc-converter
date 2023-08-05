#ifndef ADC_OPT_SMP_WIDGET_H

#define ADC_OPT_SMP_WIDGET_H

#include "widgets/abstract_widget.h"

class SmpWidget : public AbstractWidget {
    
    public:
        SmpWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
