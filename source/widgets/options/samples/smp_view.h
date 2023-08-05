#ifndef ADC_OPT_SMP_VIEW_H

#define ADC_OPT_SMP_VIEW_H

#include <QWidget>

#include "mvc/abstract_view.h"

class SmpView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
