#include <QLabel>

#include "general_model.h"
#include "general_controller.h"
#include "app/app_core.h"
#include "app/app_loader.h"
#include "app/app_mediator.h"
#include "app/workers/load_worker.h"

void GeneralController::on_View_Initialized(ElementManager* manager) {
    
    this->tuneTo(AppMediator::Channel::APP_EVENTS);
    this->tuneTo(AppMediator::Channel::STREAM_EVENTS);
    this->tuneTo(AppMediator::Channel::STREAM_PARAMS);
    
    //////////////////////////////
    
    AppLoader* loader = AppLoader::get_Instance();
    LoadWorker* worker = (LoadWorker*)loader->get_Worker();
    
    connect(worker, &LoadWorker::sig_Done,
        this, &GeneralController::on_Data_Loaded);
}

void GeneralController::on_View_Changed() {
    
    // Does nothing...
}

void GeneralController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == GeneralModel::FIELD_SAMPLES) {
        
        QLabel* samples = (QLabel*)manager
            ->get(GeneralModel::FIELD_SAMPLES);
        
        samples->setText(value);
    }
    else if (key == GeneralModel::FIELD_DURATION) {
        
        QLabel* port = (QLabel*)manager
            ->get(GeneralModel::FIELD_DURATION);
        
        port->setText(value);
    }
}

void GeneralController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QLabel* samples = (QLabel*)manager
        ->get(GeneralModel::FIELD_SAMPLES);
    
    QLabel* duration = (QLabel*)manager
        ->get(GeneralModel::FIELD_DURATION);
    
    samples->setText("N/D");
    duration->setText("N/D");
}

void GeneralController::on_Broadcast(quint64 ch, app_data_t data) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QByteArray* data_buffer = AppCore::get_Instance()->get_Buffer();
    
    QLabel* samples = (QLabel*)manager
        ->get(GeneralModel::FIELD_SAMPLES);
    
    QLabel* duration = (QLabel*)manager
        ->get(GeneralModel::FIELD_DURATION);
    
    // Stream Events
    
    if (ch == AppMediator::Channel::STREAM_EVENTS) {
        
        if (data.event == "stream_ended") {
            
            quint64 buffer_size = data_buffer->size();
            
            if (buffer_size == 0) {
                samples->setText("N/D");
            } else {
                
                quint64 total_samples  = buffer_size / (m_BitsPerSample / 8);
                qreal   total_duration = total_samples / float(m_SampleRate);
                
                samples->setText(QString::asprintf("%llu",total_samples));
                duration->setText(QString::asprintf("%.02f", total_duration));
            }
        }
    }
    
    // Stream Params
    
    else if (ch == AppMediator::Channel::STREAM_PARAMS) {
        
        quint8  bits_per_sample = data.stream_config.bits_per_sample;
        quint64 sample_rate     = data.stream_config.sample_rate;
        
        m_SampleRate    = sample_rate;
        m_BitsPerSample = bits_per_sample;
        
        quint64 buffer_size = data_buffer->size();
        
        if (buffer_size == 0) {
            samples->setText("N/D");
        } else {
            
            quint64 total_samples  = buffer_size / (bits_per_sample / 8);
            qreal   total_duration = total_samples / float(sample_rate);
            
            samples->setText(QString::asprintf("%llu",total_samples));
            duration->setText(QString::asprintf("%.02f", total_duration));
        }
    }
}

void GeneralController::on_Data_Loaded() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QLabel* samples = (QLabel*)manager
        ->get(GeneralModel::FIELD_SAMPLES);
    
    QLabel* duration = (QLabel*)manager
        ->get(GeneralModel::FIELD_DURATION);
    
    AppLoader* loader = AppLoader::get_Instance();
    
    quint64 buffer_size = loader->get_Buffer()->size();
    
    if (buffer_size == 0) {
        samples->setText("N/D");
    } else {
        
        quint64 total_samples  = buffer_size / (m_BitsPerSample / 8);
        qreal   total_duration = total_samples / float(m_SampleRate);
        
        samples->setText(QString::asprintf("%llu",total_samples));
        duration->setText(QString::asprintf("%.02f", total_duration));
    }
}
