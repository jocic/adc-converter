#ifndef ADC_AUDIO_AUDIO_SOURCE

#define ADC_AUDIO_AUDIO_SOURCE

#include <QObject>
#include <QIODevice>
#include <QByteArray>

class AudioSource : public QIODevice {
    
    Q_OBJECT
    
    private:
        quint64     m_Pointer;
        QByteArray* m_Buffer;
        quint64     m_SampleRate;
        quint8      m_BitsPerSample;
        quint64     m_TotalSamples;
        qreal       m_Duration;
        
    protected:
        void recalculate();
        qint64 readData(char *data, qint64 maxlen) override;
        qint64 writeData(const char *data, qint64 len) override;
        
    public:
        AudioSource();
        void set_Buffer(QByteArray* buffer);
        QByteArray* get_Buffer();
        void set_SampleRate(quint64 rate);
        quint64 get_SampleRate();
        void set_BitsPerSample(quint8 bps);
        quint8 get_BitsPerSample();
        quint64 get_TotalSamples();
        qreal get_Duration();
        void set_ElapsedTime(qreal time);
        qreal get_ElapsedTime();
};

#endif
