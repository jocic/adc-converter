#ifndef ADC_WIDGETS_SERIAL_WIDGET_H

#define ADC_WIDGETS_SERIAL_WIDGET_H

#include "widgets/abstract_widget.h"

class SerialWidget : public AbstractWidget {
    
    public:
        SerialWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
