#ifndef ADC_POPOVERS_ABOUT_POPOVER_H

#define ADC_POPOVERS_ABOUT_POPOVER_H

#include "popovers/abstract_popover.h"

class AboutPopover : public AbstractPopover {
    
    Q_OBJECT
    
    public:
        AboutPopover(QWidget* parent = NULL);
        void initialize() override;
};

#endif
