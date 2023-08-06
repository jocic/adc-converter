#ifndef ADC_WIDGETS_PLAYBACK_VIEW_H

#define ADC_WIDGETS_PLAYBACK_VIEW_H

#include <QWidget>

#include "mvc/abstract_view.h"

class PlaybackView : public AbstractView {
    
    public:
        void initialize(QWidget* parent) override;
};

#endif
