#ifndef ADC_TOL_PL_VIEW_H

#define ADC_TOL_PL_VIEW_H

#include <QWidget>

#include "mvc/abstract_view.h"

class PlView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
