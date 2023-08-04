#ifndef ADC_INFO_GEN_WIDGET

#define ADC_INFO_GEN_WIDGET

#include "abstract_widget.h"

class GenWidget : public AbstractWidget {
    
    public:
        GenWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
