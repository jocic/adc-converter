#ifndef ADC_OPT_SER_VIEW_H

#define ADC_OPT_SER_VIEW_H

#include <QWidget>

#include "mvc/abstract_view.h"

class SerView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
