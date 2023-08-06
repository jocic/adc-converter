#ifndef ADC_WIDGETS_GENERAL_VIEW_H

#define ADC_WIDGETS_GENERAL_VIEW_H

#include <QWidget>

#include "mvc/abstract_view.h"

class GeneralView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
