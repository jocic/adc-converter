#include <QDebug>

#include "app/data/text_processor.h"

// Example of CRAP this class was written to deal with.

//"\n-29316.33\r\n-36061.66\r\n-42446.68"
//"\r\n-48407.58\r\n-53884.82\r\n-58823.6"
//"5\r\n-63174.74\r\n-66894.61\r\n-69946."
//"09\r\n-72298.70\r\n-73928.93\r\n-74820"
//".48\r\n-74964.44\r\n-74359.38\r\n-7301"
//"1.36\r\n-70933.83\r\n-68147.54\r\n-646"

void TextProcessor::start() {
    
    m_Samples.clear();
    
    m_SkippedFirst = false;
    m_SampleBuffer = "";
    
    DataProcessor::start();
}
void TextProcessor::on_DataTimeout() {
    
    if (m_Buffers->size() == 0) {
        return;
    }
    
    quint64    index  = 0;
    QByteArray buffer = m_Buffers->dequeue();
    
    // Process Values
    
    while (index < buffer.size()) {
        
        if (buffer[index] == '\r') {
            m_Samples.enqueue(m_SampleBuffer);
            m_SampleBuffer.clear();
        } else if (buffer[index] == '\n') {
            // Do nothing...
        } else {
            m_SampleBuffer += buffer[index];
        }
        
        index++;
    }
}

void TextProcessor::on_SampleTimeout() {
    
    if (m_Samples.size() == 0) {
        return;
    }
    
    QString sample = m_Samples.dequeue();
    
    emit TextProcessor::sig_NewSample(sample.toDouble());
}
