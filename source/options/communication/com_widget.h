#ifndef ADC_OPTIONS_COM_WIDGET

#define ADC_OPTIONS_COM_WIDGET

#include "abstract_widget.h"

class ComWidget : public AbstractWidget {
    
    public:
        ComWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
