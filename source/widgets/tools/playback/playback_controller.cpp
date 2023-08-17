#include <QDebug>
#include <QByteArray>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>

#include "playback_model.h"
#include "playback_view.h"
#include "playback_controller.h"
#include "app/app_loader.h"
#include "app/app_exporter.h"

void PlaybackController::on_View_Initialized(ElementManager* manager) {
    
    // Initialize Member Variables
    
    m_SampleRate    = 44100;
    m_BitsPerSample = 8;
    
    // Connect Signals/Slots
    
    QPushButton* btn_toggle = (QPushButton*)manager
        ->get(PlaybackModel::FIELD_TOGGLE);
    
    QPushButton* btn_export = (QPushButton*)manager
        ->get(PlaybackModel::FIELD_EXPORT);
    
    connect(btn_toggle, &QPushButton::clicked,
        this, &PlaybackController::on_Clicked_Toggle);
    
    connect(btn_export, &QPushButton::clicked,
        this, &PlaybackController::on_Clicked_Export);
}

void PlaybackController::on_View_Changed() {
    
    
}

void PlaybackController::on_Model_Changed(QString key, QString value) {
    
    
}

void PlaybackController::on_Model_Cleared() {
    
    
}

void PlaybackController::on_Mediator_Notify(QString topic,
    QMap<QString,QString> params) {
    
    if (topic == "wd_stream_data") {
        
        if (params.contains("txt_SampleRate")) {
            m_SampleRate = params["txt_SampleRate"].toUInt();
        }
        
        if (params.contains("comb_BitsPerSample")) {
            m_BitsPerSample = params["comb_BitsPerSample"].toUInt();
        }
        
        qDebug() << "Received:" << m_SampleRate << m_BitsPerSample;
    }
    else if (topic == "wd_playback_request") {
        
        QString request = "none";
        
        if (params.contains("request")) {
            request = params["request"];
        }
        
        if (request == "export") {
            this->on_Clicked_Export();
        }
    }
}

void PlaybackController::on_Clicked_Toggle() {
    qDebug() << "toggle";
}

void PlaybackController::on_Clicked_Export() {
    
    // Show Dialog
    
    AppLoader*   loader   = AppLoader::get_Instance();
    AppExporter* exporter = AppExporter::get_Instance();
    
    exporter->exec();
    
    if (exporter->is_Selected()) {
        exporter->process(loader->get_Buffer(),
            m_SampleRate, m_BitsPerSample);
    }
}
