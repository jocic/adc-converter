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
    
    m_SkippedFirst = false;
    
    DataProcessor::start();
}

void TextProcessor::on_Timeout() {
    
    quint64 index  = 0;
    quint64 length = qMin(1024, m_Data->size());
    
    // Skip First Value
    
    // TO-DO: Detect ending delimiter.
    
    if (m_SkippedFirst == false) {
        
        while (index < length && m_Data->at(index) != '\n') {
            index++;
        }
        
        index++;
        
        m_SkippedFirst = true;
    }
    
    // Process Values
    
    quint64 last_index = index;
    QString sample_str = "";
    
    while (index < length) {
        
        if (m_Data->at(index) == '\r') {
            emit TextProcessor::sig_NewSample(sample_str.toDouble());
            sample_str.clear();
        } else if (m_Data->at(index) == '\n') {
            last_index = index + 1;
        } else {
            sample_str += m_Data->at(index);
        }
        
        index++;
    }
    
    if (last_index < length) {
        m_Data->erase(m_Data->begin(), m_Data->begin() + last_index);
    }
}
