#ifndef ADC_WIDGETS_DECIMAL_VIEW_H

#define ADC_WIDGETS_DECIMAL_VIEW_H

#include <QWidget>

#include "app/mvc/abstract_view.h"

class DecimalView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
