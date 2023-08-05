#ifndef ADC_OPT_COM_VIEW_H

#define ADC_OPT_COM_VIEW_H

#include <QWidget>

#include "mvc/abstract_view.h"

class ComView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
