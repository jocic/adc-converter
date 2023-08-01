#ifndef ADC_OPTIONS_REF_VIEW

#define ADC_OPTIONS_REF_VIEW

#include <QWidget>

#include "mvc/abstract_view.h"

class RefView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
