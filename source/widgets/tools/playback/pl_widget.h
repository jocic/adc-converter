#ifndef ADC_TOOLS_PL_WIDGET

#define ADC_TOOLS_PL_WIDGET

#include "widgets/abstract_widget.h"

class PlWidget : public AbstractWidget {
    
    public:
        PlWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
