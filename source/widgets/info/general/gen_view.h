#ifndef ADC_INFO_GEN_VIEW

#define ADC_INFO_GEN_VIEW

#include <QWidget>

#include "mvc/abstract_view.h"

class GenView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
