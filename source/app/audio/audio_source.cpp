#include "app/audio/audio_source.h"

AudioSource::AudioSource() {
    
    m_Pointer      = 0;
    m_Buffer       = NULL;
    m_Format       = NULL;
    m_TotalSamples = 0;
    m_Duration     = 0;
    
    this->open(QIODeviceBase::ReadOnly);
}

void AudioSource::set_Buffer(QByteArray* buffer) {
    
    if (buffer != NULL) {
        m_Buffer = buffer;
    }
}

QByteArray* AudioSource::get_Buffer() {
    return m_Buffer;
}

void AudioSource::set_Format(QAudioFormat* format) {
    
    if (format != NULL) {
        m_Format = format;
    }
}

QAudioFormat* AudioSource::get_format() {
    return m_Format;
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
    
    m_SampleRate     = m_Format->sampleRate();
    m_BytesPerSample = m_Format->bytesPerSample();
    m_BitsPerSample  = m_Format->bytesPerSample() * 8;
    
    m_TotalSamples = m_Buffer->size() / m_BytesPerSample;
    m_Duration     = m_TotalSamples / qreal(m_SampleRate);
}
