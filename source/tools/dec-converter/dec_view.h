#ifndef ADC_TOOLS_DEC_VIEW

#define ADC_TOOLS_DEC_VIEW

#include <QWidget>

#include "mvc/abstract_view.h"

class DecView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
