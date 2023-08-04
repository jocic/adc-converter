#ifndef ADC_TOOLS_DEC_WIDGET

#define ADC_TOOLS_DEC_WIDGET

#include "widgets/abstract_widget.h"

class DecWidget : public AbstractWidget {
    
    public:
        DecWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
