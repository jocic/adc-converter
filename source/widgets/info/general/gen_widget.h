#ifndef ADC_INFO_GEN_WIDGET

#define ADC_INFO_GEN_WIDGET

#include "widgets/abstract_widget.h"

class GenWidget : public AbstractWidget {
    
    public:
        GenWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
