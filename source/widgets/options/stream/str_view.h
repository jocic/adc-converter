#ifndef ADC_OPT_STR_VIEW_H

#define ADC_OPT_STR_VIEW_H

#include <QWidget>

#include "mvc/abstract_view.h"

class StrView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
