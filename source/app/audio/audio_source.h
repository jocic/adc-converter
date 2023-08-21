#ifndef ADC_AUDIO_AUDIO_SOURCE

#define ADC_AUDIO_AUDIO_SOURCE

#include <QObject>
#include <QIODevice>
#include <QByteArray>

#include <QtMultimedia/QAudioFormat>

class AudioSource : public QIODevice {
    
    Q_OBJECT
    
    private:
        quint64       m_Pointer;
        QByteArray*   m_Buffer;
        QAudioFormat* m_Format;
        quint64       m_SampleRate;
        quint8        m_BitsPerSample;
        quint8        m_BytesPerSample;
        quint64       m_TotalSamples;
        qreal         m_Duration;
        
    protected:
        qint64 readData(char *data, qint64 maxlen) override;
        qint64 writeData(const char *data, qint64 len) override;
        
    public:
        AudioSource();
        void set_Buffer(QByteArray* buffer);
        QByteArray* get_Buffer();
        void set_Format(QAudioFormat* format);
        QAudioFormat* get_format();
        quint64 get_TotalSamples();
        qreal get_Duration();
        void set_ElapsedTime(qreal time);
        qreal get_ElapsedTime();
        void recalculate();
};

#endif
