#ifndef ADC_WIDGETS_HEXADECIMAL_WIDGET_H

#define ADC_WIDGETS_HEXADECIMAL_WIDGET_H

#include "widgets/abstract_widget.h"

class HexadecimalWidget : public AbstractWidget {
    
    public:
        HexadecimalWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
