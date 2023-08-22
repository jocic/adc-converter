#ifndef ADC_WIDGETS_CONTROLS_VIEW_H

#define ADC_WIDGETS_CONTROLS_VIEW_H

#include <QWidget>

#include "app/mvc/abstract_view.h"

class ControlsView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
