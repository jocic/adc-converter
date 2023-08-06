#ifndef ADC_WIDGETS_COMMUNICATION_VIEW_H

#define ADC_WIDGETS_COMMUNICATION_VIEW_H

#include <QWidget>

#include "mvc/abstract_view.h"

class CommunicationView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
