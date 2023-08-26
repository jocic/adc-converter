#include "app/data/data_processor.h"

DataProcessor::DataProcessor() {
    
    m_Timer = new QTimer();
    
    connect(m_Timer, &QTimer::timeout,
        this, &DataProcessor::on_Timeout);
    
    ////////////////////////////
    
    m_Data = new QByteArray();
}

void DataProcessor::start() {
    
    if (m_Timer->isActive()) {
        return;
    }
    
    m_Timer->start();
    
    emit DataProcessor::sig_Started();
}

void DataProcessor::stop() {
    
    if (!m_Timer->isActive()) {
        return;
    }
    
    m_Timer->stop();
    
    emit DataProcessor::sig_Stopped();
}

void DataProcessor::pushData(QByteArray buffer) {
    *m_Data += buffer;
}

void DataProcessor::on_NewData(QByteArray buffer) {
    this->pushData(buffer);
}
