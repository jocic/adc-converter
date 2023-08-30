#ifndef ADC_WIDGETS_PLAYBACK_CONTROLLER_H

#define ADC_WIDGETS_PLAYBACK_CONTROLLER_H

#include "app/mvc/abstract_controller.h"
#include "app/workers/play_worker.h"

class PlaybackController : public AbstractController {
    
    private:
        PlayWorker* m_Worker;
        quint64     m_SampleRate;
        quint8      m_BitsPerSample;
        bool        m_Playing;
    
    public slots:
        void on_View_Initialized(ElementManager* manager) override;
        void on_View_Changed() override;
        void on_Model_Changed(QString key, QString value) override;
        void on_Model_Cleared() override;
        void on_Broadcast(QString topic, QMap<QString,QString> params) override;
        void on_Broadcast_ALT(QString topic, void* params) override;
        void on_Playback_Update(qreal time);
        void on_Audio_Started();
        void on_Audio_Stopped();
        void on_Clicked_Toggle();
        void on_Clicked_Export();
};

#endif
