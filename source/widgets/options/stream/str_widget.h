#ifndef ADC_OPT_STR_WIDGET_H

#define ADC_OPT_STR_WIDGET_H

#include "widgets/abstract_widget.h"

class StrWidget : public AbstractWidget {
    
    public:
        StrWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
