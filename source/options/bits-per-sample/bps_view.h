#ifndef ADC_OPTIONS_BPS_VIEW

#define ADC_OPTIONS_BPS_VIEW

#include <QWidget>

#include "mvc/abstract_view.h"

class BpsView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
