#ifndef ADC_WIDGETS_GENERAL_WIDGET_H

#define ADC_WIDGETS_GENERAL_WIDGET_H

#include "widgets/abstract_widget.h"

class GeneralWidget : public AbstractWidget {
    
    public:
        GeneralWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
