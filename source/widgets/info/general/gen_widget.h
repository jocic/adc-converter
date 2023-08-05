#ifndef ADC_INF_GEN_WIDGET_H

#define ADC_INF_GEN_WIDGET_H

#include "widgets/abstract_widget.h"

class GenWidget : public AbstractWidget {
    
    public:
        GenWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
