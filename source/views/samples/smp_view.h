#ifndef ADC_VEW_SMP_VIEW_H

#define ADC_VEW_SMP_VIEW_H

#include <QWidget>

#include "mvc/abstract_view.h"

class SmpView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
    
    private:
        QWidget* make_Overview();
        QWidget* make_Navigator();
        QWidget* make_Offseter();
};

#endif
