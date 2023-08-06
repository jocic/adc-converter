#ifndef ADC_WIDGETS_STREAM_VIEW_H

#define ADC_WIDGETS_STREAM_VIEW_H

#include <QWidget>

#include "mvc/abstract_view.h"

class StreamView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
