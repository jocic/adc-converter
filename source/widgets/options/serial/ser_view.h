#ifndef ADC_OPTIONS_SER_VIEW

#define ADC_OPTIONS_SER_VIEW

#include <QWidget>

#include "mvc/abstract_view.h"

class SerView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
