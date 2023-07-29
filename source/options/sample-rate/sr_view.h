#ifndef ADC_OPTIONS_SR_VIEW

#define ADC_OPTIONS_SR_VIEW

#include <QWidget>

#include "mvc/abstract_view.h"

class SrView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
