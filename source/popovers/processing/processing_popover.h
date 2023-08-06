#ifndef ADC_POPOVERS_PROCESSING_POPOVER_H

#define ADC_POPOVERS_PROCESSING_POPOVER_H

#include "popovers/abstract_popover.h"

class ProcessingPopover : public AbstractPopover {
    
    public:
        ProcessingPopover(QWidget* parent = NULL);
        void initialize() override;
};

#endif
