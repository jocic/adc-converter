#ifndef ADC_TOL_DEC_VIEW_H

#define ADC_TOL_DEC_VIEW_H

#include <QWidget>

#include "mvc/abstract_view.h"

class DecView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
