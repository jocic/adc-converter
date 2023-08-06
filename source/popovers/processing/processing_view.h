#ifndef ADC_POPOVERS_PROCESSING_VIEW_H

#define ADC_POPOVERS_PROCESSING_VIEW_H

#include "mvc/abstract_view.h"

class ProcessingView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
