#ifndef ADC_WIDGET_CONTROLS_WIDGET_H

#define ADC_WIDGET_CONTROLS_WIDGET_H

#include "widgets/abstract_widget.h"

class ControlsWidget : public AbstractWidget {
    
    public:
        ControlsWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
