#ifndef ADC_WIDGETS_DECIMAL_WIDGET_H

#define ADC_WIDGETS_DECIMAL_WIDGET_H

#include "widgets/abstract_widget.h"

class DecimalWidget : public AbstractWidget {
    
    public:
        DecimalWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
