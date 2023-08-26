#include "app/data/data_processor.h"

DataProcessor::DataProcessor() {
    
    m_DataTimer = new QTimer();
    
    connect(m_DataTimer, &QTimer::timeout,
        this, &DataProcessor::on_DataTimeout);
    
    ////////////////////////////
    
    m_SampleTimer = new QTimer();
    
    m_SampleTimer->setInterval(1);
    
    connect(m_SampleTimer, &QTimer::timeout,
        this, &DataProcessor::on_SampleTimeout);
    
    ////////////////////////////
    
    m_Data = new QByteArray();
}

void DataProcessor::start() {
    
    if (m_DataTimer->isActive()) {
        return;
    }
    
    m_DataTimer->start();
    m_SampleTimer->start();
    
    emit DataProcessor::sig_Started();
}

void DataProcessor::stop() {
    
    if (!m_DataTimer->isActive()) {
        return;
    }
    
    m_DataTimer->stop();
    m_SampleTimer->stop();
    
    emit DataProcessor::sig_Stopped();
}

void DataProcessor::pushData(QByteArray buffer) {
    *m_Data += buffer;
}

void DataProcessor::on_NewData(QByteArray buffer) {
    this->pushData(buffer);
}
