#ifndef ADC_OPTIONS_PL_VIEW

#define ADC_OPTIONS_PL_VIEW

#include <QWidget>

#include "mvc/abstract_view.h"

class PlView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
