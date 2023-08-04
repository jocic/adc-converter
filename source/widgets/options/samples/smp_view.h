#ifndef ADC_OPTIONS_SMP_VIEW

#define ADC_OPTIONS_SMP_VIEW

#include <QWidget>

#include "mvc/abstract_view.h"

class SmpView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
