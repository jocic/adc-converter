#ifndef ADC_OPT_COM_WIDGET_H

#define ADC_OPT_COM_WIDGET_H

#include "widgets/abstract_widget.h"

class ComWidget : public AbstractWidget {
    
    public:
        ComWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
