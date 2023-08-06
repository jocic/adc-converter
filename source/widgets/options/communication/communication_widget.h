#ifndef ADC_WIDGET_COMMUNICATION_WIDGET_H

#define ADC_WIDGET_COMMUNICATION_WIDGET_H

#include "widgets/abstract_widget.h"

class CommunicationWidget : public AbstractWidget {
    
    public:
        CommunicationWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
