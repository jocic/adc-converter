#ifndef ADC_OPTIONS_REF_WIDGET

#define ADC_OPTIONS_REF_WIDGET

#include "widgets/abstract_widget.h"

class RefWidget : public AbstractWidget {
    
    public:
        RefWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
