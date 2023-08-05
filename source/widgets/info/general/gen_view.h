#ifndef ADC_INF_GEN_VIEW_H

#define ADC_INF_GEN_VIEW_H

#include <QWidget>

#include "mvc/abstract_view.h"

class GenView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
