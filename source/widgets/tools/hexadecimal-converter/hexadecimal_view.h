#ifndef ADC_WIDGETS_HEXADECIMAL_VIEW_H

#define ADC_WIDGETS_HEXADECIMAL_VIEW_H

#include <QWidget>

#include "mvc/abstract_view.h"

class HexadecimalView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
