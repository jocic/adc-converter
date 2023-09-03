#include <QDebug>

#include "app/data/binary_processor.h"

BinaryProcessor::BinaryProcessor() : DataProcessor() {
    
    m_Samples = new QQueue<qint32>();
}

void BinaryProcessor::start(quint8 bits_per_sample, bool big_endian) {
    
    m_BitsPerSample = bits_per_sample;
    m_BigEndian     = big_endian;
    
    m_Buffers->clear();
    m_Samples->clear();
    
    m_SampleBuffer = 0;
    m_BitsCount    = 0;
    
    DataProcessor::start();
}

void BinaryProcessor::stop() {
    
    while (m_Samples->size() > 0) {
        qint32 sample = m_Samples->dequeue();
        emit BinaryProcessor::sig_NewSample(sample);
    }
    
    DataProcessor::stop();
}

void BinaryProcessor::on_DataTimeout() {
    
    if (m_Buffers->size() == 0) {
        return;
    }
    
    quint64    index  = 0;
    QByteArray buffer = m_Buffers->dequeue();
    
    // Process Values
    
    while (index < buffer.size()) {
        
        m_BitsCount += 8;
        
        if (m_BigEndian) {
            
            m_SampleBuffer <<= 8;
            m_SampleBuffer  |= buffer[index];
            
            if (m_BitsCount == m_BitsPerSample) {
                m_Samples->enqueue(m_SampleBuffer);
                m_SampleBuffer = m_BitsCount = 0;
            }
        }
        else {
            
            m_SampleBuffer |= buffer[index];
            
            if (m_BitsCount == m_BitsPerSample) {
                m_Samples->enqueue(m_SampleBuffer);
                m_SampleBuffer = m_BitsCount = 0;
            }
            
            m_SampleBuffer <<= 8;
        }
        
        index++;
    }
}

void BinaryProcessor::on_SampleTimeout() {
    
    if (m_Samples->size() == 0) {
        return;
    }
    
    qint32 sample = m_Samples->dequeue();
    
    emit BinaryProcessor::sig_NewSample(sample);
}
