#include "app/audio/audio_source.h"

AudioSource::AudioSource() {
    
    m_Pointer       = 0;
    m_Buffer        = NULL;
    m_SampleRate    = 44100;
    m_BitsPerSample = 16;
    m_Duration      = 0;
    
}

void AudioSource::set_Buffer(QByteArray* buffer) {
    
    if (buffer != NULL) {
        m_Buffer = buffer;
    }
}

QByteArray* AudioSource::get_Buffer() {
    return m_Buffer;
}

void AudioSource::set_SampleRate(quint64 rate) {
    m_SampleRate = rate;
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
}

quint8 AudioSource::get_BitsPerSample() {
    return m_BitsPerSample;
}

qreal AudioSource::get_Duration() {
    
    quint64 total_samples = m_Buffer->size() / (m_BitsPerSample / 8);
    
    return total_samples / qreal(m_SampleRate);
}

void AudioSource::set_ElapsedTime(qreal time) {
    
    quint64 pos = time * m_SampleRate * (m_BitsPerSample / 8);
    
    if (pos < m_Buffer->size()) {
        m_Pointer = pos;
    }
}

qreal AudioSource::get_ElapsedTime() {
    
    qreal duration = this->get_Duration();
    
    return duration * (m_Pointer / qreal(m_Buffer->size()));
}

qint64 AudioSource::readData(char *data, qint64 maxlen) {
    
    quint64 i = 0;
    
    while (i < maxlen && m_Pointer < m_Buffer->size()) {
        data[i++] = (*m_Buffer[m_Pointer++] & 0xFF);
    }
    
    return i;
}

qint64 AudioSource::writeData(const char *data, qint64 len) {
    return 0;
}
