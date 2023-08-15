#ifndef ADC_WIDGETS_SERIAL_VIEW_H

#define ADC_WIDGETS_SERIAL_VIEW_H

#include <QWidget>

#include "app/mvc/abstract_view.h"

class SerialView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
