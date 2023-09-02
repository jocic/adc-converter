#include <QDebug>

#include "app/data/binary_processor.h"

BinaryProcessor::BinaryProcessor() : DataProcessor() {
    
    m_Samples      = new QQueue<qint32>();
    m_SampleBuffer = new QByteArray();
}

void BinaryProcessor::start() {
    
    m_Buffers->clear();
    m_Samples->clear();
    
    DataProcessor::start();
}

void BinaryProcessor::stop() {
    
    while (m_Samples->size() > 0) {
        qint32 sample = m_Samples->dequeue();
        emit BinaryProcessor::sig_NewSample(sample);
    }
    
    DataProcessor::stop();
}

int test = 0;

qint16 sample = 0;

void BinaryProcessor::on_DataTimeout() {
    
    if (m_Buffers->size() == 0) {
        return;
    }
    
    quint64    index  = 0;
    QByteArray buffer = m_Buffers->dequeue();
    
    // Process Values
    
    while (index < buffer.size()) {
        
        sample <<= 8;
        sample  |= buffer[index];
        
        test++;
        
        if (test == 2) {
            m_Samples->enqueue(sample);
            sample = test = 0;
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
