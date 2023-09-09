#ifndef ADC_WORKERS_PLAY_WORKER_H

#define ADC_WORKERS_PLAY_WORKER_H

#include <QObject>
#include <QFile>

#include <QtMultimedia/QAudio>
#include <QtMultimedia/QAudioSink>
#include <QtMultimedia/QAudioFormat>

#include "app/workers/abstract_file_worker.h"
#include "app/audio/audio_source.h"

class PlayWorker : public AbstractFileWorker {
    
    Q_OBJECT
    
    protected:
        QAudioSink*   m_Sink;
        QAudioFormat* m_Format;
        AudioSource*  m_Source;
    
    protected:
        void on_StateChanged(QAudio::State state);
    
    public:
        PlayWorker();
        void play(qreal time = 0);
        void stop();
        QAudioSink* get_Sink();
        QAudioFormat* get_Format();
        AudioSource* get_Source();
        void run() override;
    
    signals:
        void sig_Started();
        void sig_Stopped();
        void sig_Update(qreal time);
};

#endif
