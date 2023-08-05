#ifndef ADC_OPT_SER_WIDGET_H

#define ADC_OPT_SER_WIDGET_H

#include "widgets/abstract_widget.h"

class SerWidget : public AbstractWidget {
    
    public:
        SerWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
