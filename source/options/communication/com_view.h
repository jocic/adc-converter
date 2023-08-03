#ifndef ADC_OPTIONS_COM_VIEW

#define ADC_OPTIONS_COM_VIEW

#include <QWidget>

#include "mvc/abstract_view.h"

class ComView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
