#ifndef ADC_TOL_HEX_VIEW_H

#define ADC_TOL_HEX_VIEW_H

#include <QWidget>

#include "mvc/abstract_view.h"

class HexView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
