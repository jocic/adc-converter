#ifndef ADC_WIDGETS_PLAYBACK_CONTROLLER_H

#define ADC_WIDGETS_PLAYBACK_CONTROLLER_H

#include "app/mvc/abstract_controller.h"

#include <QtMultimedia/QAudioSink>
#include "app/audio/audio_source.h"

class PlaybackController : public AbstractController {
    
    private:
        quint64 m_SampleRate;
        quint8  m_BitsPerSample;
        bool    m_Playing;
        
        QAudioSink* audio_sink;
        
        AudioSource* audio_source;
    
    public slots:
        void on_View_Initialized(ElementManager* manager) override;
        void on_View_Changed() override;
        void on_Model_Changed(QString key, QString value) override;
        void on_Model_Cleared() override;
        void on_Mediator_Notify(QString topic, QMap<QString,QString> params) override;
        void on_Moved_Playback(int value);
        void on_Clicked_Toggle();
        void on_Clicked_Export();
};

#endif
