#ifndef ADC_TOL_HEX_WIDGET_H

#define ADC_TOL_HEX_WIDGET_H

#include "widgets/abstract_widget.h"

class HexWidget : public AbstractWidget {
    
    public:
        HexWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
