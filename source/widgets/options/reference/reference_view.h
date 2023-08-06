#ifndef ADC_WIDGETS_REFERENCE_VIEW_H

#define ADC_WIDGETS_REFERENCE_VIEW_H

#include <QWidget>

#include "mvc/abstract_view.h"

class ReferenceView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
