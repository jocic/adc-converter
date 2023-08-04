#ifndef ADC_TOOLS_HEX_WIDGET

#define ADC_TOOLS_HEX_WIDGET

#include "widgets/abstract_widget.h"

class HexWidget : public AbstractWidget {
    
    public:
        HexWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
