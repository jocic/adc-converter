#ifndef ADC_OPTIONS_PL_WIDGET

#define ADC_OPTIONS_PL_WIDGET

#include "abstract_widget.h"

class PlWidget : public AbstractWidget {
    
    public:
        PlWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
