#ifndef ADC_TOOLS_HEX_VIEW

#define ADC_TOOLS_HEX_VIEW

#include <QWidget>

#include "mvc/abstract_view.h"

class HexView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
