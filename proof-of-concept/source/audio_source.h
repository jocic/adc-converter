#ifndef AUDIO_SOURCE_H
#define AUDIO_SOURCE_H

#include <QIODevice>
#include <QByteArray>

class AudioSource : public QIODevice
{
    Q_OBJECT
    
    private:
        qint64     pos = 0;
        QByteArray buffer;
    
    public:
        AudioSource();
        bool loadSamples(const char* filename);
        bool setSamples(QVector<qint64>& samples, int bits);
        
    protected:
        qint64 readData(char *data, qint64 maxlen) override;
        qint64 writeData(const char *data, qint64 len) override;
};

#endif // AUDIO_SOURCE_H
