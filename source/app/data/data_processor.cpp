#include "app/data/data_processor.h"

DataProcessor::DataProcessor() {
    
    m_DataTimer = new QTimer();
    
    connect(m_DataTimer, &QTimer::timeout,
        this, &DataProcessor::on_DataTimeout);
    
    ////////////////////////////
    
    m_SampleTimer = new QTimer();
    
    connect(m_SampleTimer, &QTimer::timeout,
        this, &DataProcessor::on_SampleTimeout);
    
    ////////////////////////////
    
    m_Buffers = new QQueue<QByteArray>();
}

void DataProcessor::start() {
    
    if (!m_DataTimer->isActive()) {
        m_DataTimer->start();
    }
    
    if (!m_SampleTimer->isActive()) {
        m_SampleTimer->start();
    }
    
    emit DataProcessor::sig_Started();
}

void DataProcessor::stop() {
    
    m_Buffers->clear();
    
    if (m_DataTimer->isActive()) {
        m_DataTimer->stop();
    }
    
    if (m_SampleTimer->isActive()) {
        m_SampleTimer->stop();
    }
    
    emit DataProcessor::sig_Stopped();
}

void DataProcessor::pushData(QByteArray buffer) {
    m_Buffers->enqueue(buffer);
}

void DataProcessor::on_NewData(QByteArray buffer) {
    this->pushData(buffer);
}
