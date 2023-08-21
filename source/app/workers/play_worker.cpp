#include "app/app_loader.h"
#include "app/workers/play_worker.h"

PlayWorker::PlayWorker() {
    
    AppLoader* loader = AppLoader::get_Instance();
    
    m_Sink = NULL;
    
    m_Format = new QAudioFormat();
    m_Source = new AudioSource();
    
    m_Format->setSampleRate(44100);
    m_Format->setChannelCount(1);
    m_Format->setSampleFormat(QAudioFormat::SampleFormat::Int16);
    
    m_Source->set_Format(m_Format);
    m_Source->set_Buffer(loader->get_Buffer());
    m_Source->set_ElapsedTime(0);
    
    m_Source->recalculate();
    
    this->start();
}

void PlayWorker::play(qreal time) {
    
    if (m_Sink != NULL) {
        m_Sink->suspend();
        m_Sink->stop();
        delete m_Sink;
    }
    
    m_Source->set_ElapsedTime(time);
    m_Source->recalculate();
    
    m_Sink = new QAudioSink(*m_Format, NULL);
    
    m_Sink->start(m_Source);
    
    connect(m_Sink, &QAudioSink::stateChanged,
        this, &PlayWorker::on_StateChanged);
}

void PlayWorker::stop() {
    
    if (m_Sink != NULL) {
        m_Sink->suspend();
        m_Sink->stop();
        delete m_Sink;
    }
    
    m_Sink = NULL;
}

QAudioSink* PlayWorker::get_Sink() {
    return m_Sink;
}

QAudioFormat* PlayWorker::get_Format() {
    return m_Format;
}

AudioSource* PlayWorker::get_Source() {
    return m_Source;
}

void PlayWorker::run() {
    
    qreal last = 0, current = 0;
    
    while (true) {
        
        this->msleep(10);
        
        if ((current = m_Source->get_ElapsedTime()) != last) {
            last = current;
            emit PlayWorker::sig_Update(current);
        }
    }
}

void PlayWorker::on_StateChanged(QAudio::State state) {
    
    if (state == QAudio::State::ActiveState) {
        emit PlayWorker::sig_Started();
    } else if (   state == QAudio::State::IdleState
               || state == QAudio::State::StoppedState) {
       emit PlayWorker::sig_Stopped();
   }
}
