#ifndef ADC_TOL_PL_WIDGET_H

#define ADC_TOL_PL_WIDGET_H

#include "widgets/abstract_widget.h"

class PlWidget : public AbstractWidget {
    
    public:
        PlWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
