#ifndef ADC_OPT_REF_VIEW_H

#define ADC_OPT_REF_VIEW_H

#include <QWidget>

#include "mvc/abstract_view.h"

class RefView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
