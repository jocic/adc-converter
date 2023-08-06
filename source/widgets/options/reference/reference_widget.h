#ifndef ADC_WIDGETS_REFERENCE_WIDGET_H

#define ADC_WIDGETS_REFERENCE_WIDGET_H

#include "widgets/abstract_widget.h"

class ReferenceWidget : public AbstractWidget {
    
    public:
        ReferenceWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
