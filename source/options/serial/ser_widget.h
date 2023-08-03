#ifndef ADC_OPTIONS_SER_WIDGET

#define ADC_OPTIONS_SER_WIDGET

#include "abstract_widget.h"

class SerWidget : public AbstractWidget {
    
    public:
        SerWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
