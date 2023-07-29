#ifndef ADC_OPTIONS_BPS_WIDGET

#define ADC_OPTIONS_BPS_WIDGET

#include "abstract_widget.h"

class BpsWidget : public AbstractWidget {
    
    public:
        
        BpsWidget(QWidget* parent = NULL) : AbstractWidget(parent) {
            
        }
        
        void initialize() override;
};

#endif
