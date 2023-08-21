#ifndef ADC_VEWES_SCOPE_WIDGET_H

#define ADC_VEWES_SCOPE_WIDGET_H

#include "widgets/abstract_widget.h"

class ScopeWidget : public AbstractWidget {
    
    public:
        ScopeWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
