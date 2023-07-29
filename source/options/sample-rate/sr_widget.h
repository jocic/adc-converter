#ifndef ADC_OPTIONS_SR_WIDGET

#define ADC_OPTIONS_SR_WIDGET

#include "abstract_widget.h"

class SrWidget : public AbstractWidget {
    
    public:
        SrWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
