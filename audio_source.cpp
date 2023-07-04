#include <QDebug>
#include <QFile>

#include "audio_source.h"

AudioSource::AudioSource() {
    
    QIODevice::open(QIODevice::ReadWrite);
}

bool AudioSource::loadSamples(const char* filename) {
    
    this->pos = 0;
    
    QFile file(filename);
    
    file.open(QFile::ReadOnly);
    
    if (!file.isOpen()) {
        return false;
    }
    
    this->buffer = file.readAll();
    
    file.close();
    
    return true;
}

bool AudioSource::setSamples(QVector<qint64>& samples, int bits) {
    
    this->pos = 0;
    
    this->buffer.clear();
    
    for (const auto& sample : samples) {
        
        if (bits == 8) {
            this->buffer.push_back(sample & 0xFF);
        } else if (bits == 16) {
            this->buffer.push_back(sample & 0xFF);
            this->buffer.push_back((sample >> 8) & 0xFF);
        } else if (bits == 32) {
            this->buffer.push_back(sample & 0xFF);
            this->buffer.push_back((sample >> 8) & 0xFF);
            this->buffer.push_back((sample >> 16) & 0xFF);
            this->buffer.push_back((sample >> 24) & 0xFF);
        }
    }
    
    return true;
}

qint64 AudioSource::readData(char *data, qint64 maxlen) {
    
    int i = 0;
    
    while (i < maxlen && this->pos < this->buffer.size()) {
        data[i++] = (this->buffer[this->pos++] & 0xFF);
    }
    
    return i;
}

qint64 AudioSource::writeData(const char *data, qint64 len) {
    return 0;
}
