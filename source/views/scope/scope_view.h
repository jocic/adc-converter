#ifndef ADC_VIEWS_SCOPE_VIEW_H

#define ADC_VIEWS_SCOPE_VIEW_H

#include <QWidget>

#include "app/mvc/abstract_view.h"

class ScopeView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
