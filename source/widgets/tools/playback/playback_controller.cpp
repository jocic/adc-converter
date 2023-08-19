#include <QDebug>
#include <QByteArray>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QSlider>
#include <QPushButton>

#include "playback_model.h"
#include "playback_view.h"
#include "playback_controller.h"
#include "app/app_icons.h"
#include "app/app_loader.h"
#include "app/app_exporter.h"

void PlaybackController::on_View_Initialized(ElementManager* manager) {
    
    // Initialize Member Variables
    
    m_SampleRate    = 44100;
    m_BitsPerSample = 8;
    
    // Connect Signals/Slots
    
    QSlider* slide_Time = (QSlider*)manager
        ->get(PlaybackModel::FIELD_PLAYBACK_TIME);
    
    QPushButton* btn_toggle = (QPushButton*)manager
        ->get(PlaybackModel::FIELD_TOGGLE);
    
    QPushButton* btn_export = (QPushButton*)manager
        ->get(PlaybackModel::FIELD_EXPORT);
    
    connect(slide_Time, &QSlider::sliderMoved,
        this, &PlaybackController::on_Moved_Playback);
    
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

void PlaybackController::on_Moved_Playback(int value) {
    qDebug() << value;
}

#include <QtMultimedia/QMediaDevices>
#include <QtMultimedia/QAudioSink>
#include <QtMultimedia/QAudioDevice>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioOutput>

#include "app/audio/audio_source.h"

void PlaybackController::on_Clicked_Toggle() {
    
    QAudioDevice audio_device = QMediaDevices::defaultAudioOutput();
    
    if (audio_device.isNull()) {
        // error - no output device on the machine
    }
    
    QAudioFormat audio_format;
    
    qDebug() << m_SampleRate << m_BitsPerSample;
    
    audio_format.setChannelCount(1);
    audio_format.setSampleRate(m_SampleRate);
    
    switch (m_BitsPerSample) {
        case 8:
            audio_format.setSampleFormat(QAudioFormat::SampleFormat::UInt8);
            break;
        case 16:
            audio_format.setSampleFormat(QAudioFormat::SampleFormat::Int16);
            break;
        case 24:
        case 32:
            audio_format.setSampleFormat(QAudioFormat::SampleFormat::Int32);
            break;
        default:
            ; // error
    }
    
    if (!audio_device.isFormatSupported(audio_format)) {
        // warning - sample rate/bits per sample not natively supported by the device
    }
    
    audio_source = new AudioSource();
    
    AppLoader* loader = AppLoader::get_Instance();
    
    audio_source->set_Buffer(loader->get_Buffer());
    audio_source->set_SampleRate(m_SampleRate);
    audio_source->set_BitsPerSample(m_BitsPerSample);
    
    audio_sink = new QAudioSink(audio_format, NULL);
    
    audio_sink->start(audio_source);
    
    /////////////
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QPushButton* btn_toggle = (QPushButton*)manager
        ->get(PlaybackModel::FIELD_TOGGLE);
    
    if (m_Playing) {
        btn_toggle->setText("Play");
        btn_toggle->setIcon(*AppIcons::PLAY);
    } else {
        btn_toggle->setText("Stop");
        btn_toggle->setIcon(*AppIcons::STOP);
    }
    
    m_Playing = !m_Playing;
}

void PlaybackController::on_Clicked_Export() {
    
    QString export_filename = "export_" +
        QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".wav";
    
    // Show Dialog
    
    AppLoader*   loader   = AppLoader::get_Instance();
    AppExporter* exporter = AppExporter::get_Instance();
    
    exporter->selectFile(export_filename);
    exporter->exec();
    
    if (exporter->is_Selected()) {
        exporter->process(loader->get_Buffer(), m_SampleRate, m_BitsPerSample);
    }
}
