#ifndef ADC_TOL_DEC_WIDGET_H

#define ADC_TOL_DEC_WIDGET_H

#include "widgets/abstract_widget.h"

class DecWidget : public AbstractWidget {
    
    public:
        DecWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
