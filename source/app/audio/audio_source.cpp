#include "app/audio/audio_source.h"

AudioSource::AudioSource() {
    
    m_Pointer       = 0;
    m_Buffer        = NULL;
    m_SampleRate    = 44100;
    m_BitsPerSample = 16;
    m_Duration      = 0;
    
    this->open(QIODeviceBase::ReadOnly);
}

void AudioSource::set_Buffer(QByteArray* buffer) {
    
    if (buffer != NULL) {
        
        m_Buffer = buffer;
        
        this->recalculate();
    }
}

QByteArray* AudioSource::get_Buffer() {
    return m_Buffer;
}

void AudioSource::set_SampleRate(quint64 rate) {
    
    m_SampleRate = rate;
    
    this->recalculate();
}

quint64 AudioSource::get_SampleRate() {
    return m_SampleRate;
}

void AudioSource::set_BitsPerSample(quint8 bps) {
    
    switch (bps) {
        
        case 8:
        case 16:
        case 24:
        case 32:
            m_BitsPerSample = bps;
            break;
            
        default:
            m_BitsPerSample = 8;
    }
    
    this->recalculate();
}

quint8 AudioSource::get_BitsPerSample() {
    return m_BitsPerSample;
}

quint64 AudioSource::get_TotalSamples() {
    return m_TotalSamples;
}

qreal AudioSource::get_Duration() {
    return m_Duration;
}

void AudioSource::set_ElapsedTime(qreal time) {
    
    if (m_Buffer != NULL) {
        
        quint64 pos = time * m_SampleRate * (m_BitsPerSample / 8);
        
        if (pos < m_Buffer->size()) {
            m_Pointer = pos;
        }
    }
}

qreal AudioSource::get_ElapsedTime() {
    
    if (m_Buffer != NULL) {
        
        qreal duration = this->get_Duration();
        
        return duration * (m_Pointer / qreal(m_Buffer->size()));
    }
    
    return 0;
}

qint64 AudioSource::readData(char *data, qint64 maxlen) {
    
    quint64 i = 0;
    
    char* buffer_data = m_Buffer->data();
    
    while (i < maxlen && m_Pointer < m_Buffer->size()) {
        data[i++] = (buffer_data[m_Pointer++] & 0xFF);
    }
    
    return i;
}

qint64 AudioSource::writeData(const char *data, qint64 len) {
    return 0;
}

void AudioSource::recalculate() {
    
    quint64 total_samples = m_Buffer->size() / (m_BitsPerSample / 8);
    
    m_TotalSamples = total_samples;
    m_Duration     = total_samples / qreal(m_SampleRate);
}
