#ifndef ADC_OPT_REF_WIDGET_H

#define ADC_OPT_REF_WIDGET_H

#include "widgets/abstract_widget.h"

class RefWidget : public AbstractWidget {
    
    public:
        RefWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
