#ifndef ADC_WIDGETS_PLAYBACK_WIDGET_H

#define ADC_WIDGETS_PLAYBACK_WIDGET_H

#include "widgets/abstract_widget.h"

class PlaybackWidget : public AbstractWidget {
    
    public:
        PlaybackWidget(QWidget* parent = NULL);
        void initialize() override;
};

#endif
