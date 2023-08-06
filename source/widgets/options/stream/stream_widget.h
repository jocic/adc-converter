#ifndef ADC_WIDGETS_STREAM_WIDGET_H

#define ADC_WIDGETS_STREAM_WIDGET_H

#include "widgets/abstract_widget.h"

class StreamWidget : public AbstractWidget {
    
    public:
        StreamWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
