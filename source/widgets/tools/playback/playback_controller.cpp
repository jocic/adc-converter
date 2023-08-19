#include <QDebug>
#include <QByteArray>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QSlider>
#include <QPushButton>

#include <QtMultimedia/QMediaDevices>
#include <QtMultimedia/QAudioSink>
#include <QtMultimedia/QAudioDevice>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioOutput>

#include "playback_model.h"
#include "playback_view.h"
#include "playback_controller.h"
#include "app/app_icons.h"
#include "app/app_loader.h"
#include "app/app_exporter.h"

void PlaybackController::on_View_Initialized(ElementManager* manager) {
    
    // Initialize Member Variables
    
    m_AudioSink     = NULL;
    m_AudioSource   = NULL;
    m_SampleRate    = 44100;
    m_BitsPerSample = 8;
    
    // Connect Signals/Slots
    
    QSlider* slide_Time = (QSlider*)manager
        ->get(PlaybackModel::FIELD_PLAYBACK_TIME);
    
    QPushButton* btn_toggle = (QPushButton*)manager
        ->get(PlaybackModel::FIELD_TOGGLE);
    
    QPushButton* btn_export = (QPushButton*)manager
        ->get(PlaybackModel::FIELD_EXPORT);
    
    connect(slide_Time, &QSlider::valueChanged,
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

void PlaybackController::on_Sink_State(QAudio::State state) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QPushButton* btn_toggle = (QPushButton*)manager
        ->get(PlaybackModel::FIELD_TOGGLE);
    
    if (state == QAudio::State::ActiveState) {
        m_Playing = true;
        btn_toggle->setText("Stop");
        btn_toggle->setIcon(*AppIcons::STOP);
        
    } else if (state == QAudio::State::IdleState || state == QAudio::State::StoppedState) {
        m_Playing = false;
        btn_toggle->setText("Play");
        btn_toggle->setIcon(*AppIcons::PLAY);
    }
}

void PlaybackController::on_Moved_Playback(int value) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QSlider* slide_Time = (QSlider*)manager
        ->get(PlaybackModel::FIELD_PLAYBACK_TIME);
    
    if (m_AudioSource != NULL) {
        
        qreal duration = m_AudioSource->get_Duration();
        qreal jump_to  = (duration * (value + 1)) / slide_Time->maximum();
        
        quint64 temp = jump_to * 100 + 0.5F;
        
        quint64 rem = temp % 25;
        
        if (rem != 0) {
            temp += 25 - rem;
        }
        
        jump_to = temp / 100.0F;
        
        qDebug() << "Jumping to:" << jump_to;
        
        m_AudioSink->stop();
        
        m_AudioSource->set_ElapsedTime(jump_to);
        
        m_AudioSink->start(m_AudioSource);
    }
}

void PlaybackController::on_Clicked_Toggle() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QPushButton* btn_toggle = (QPushButton*)manager
        ->get(PlaybackModel::FIELD_TOGGLE);
    
    // Handle Previous Sink
    
    if (m_AudioSink != NULL) {
        
        if (m_AudioSink->state() == QAudio::State::ActiveState) {        
            m_AudioSink->stop();
            return;
        }
    }
    
    // Handle Request
    
    if (!m_Playing) {
        
        // Get Default Audio Output
        
        QAudioDevice audio_device = QMediaDevices::defaultAudioOutput();
        
        if (audio_device.isNull()) {
            QMessageBox error;
            error.setWindowTitle("System Error");
            error.setText("No output device on the machine.");
            error.exec();
            return;
        }
        
        // Set Audio Format
        
        QAudioFormat audio_format;
        
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
                QMessageBox error;
                error.setWindowTitle("Program Error");
                error.setText("Bits per sample value is invalid.");
                error.exec();
                return;
        }
        
        if (!audio_device.isFormatSupported(audio_format)) {
            QMessageBox warning;
            warning.setWindowTitle("Warning!");
            warning.setText("Selected stream configuration is not natively "
                "supported by your output device.");
            warning.exec();
        }
        
        if (m_AudioSource == NULL) {
            m_AudioSource = new AudioSource();
        }
        
        AppLoader* loader = AppLoader::get_Instance();
        
        m_AudioSource->set_Buffer(loader->get_Buffer());
        m_AudioSource->set_SampleRate(m_SampleRate);
        m_AudioSource->set_BitsPerSample(m_BitsPerSample);
        m_AudioSource->set_ElapsedTime(0);
        
        if (m_AudioSink == NULL) {
            m_AudioSink = new QAudioSink(audio_format, NULL);
            connect(m_AudioSink, &QAudioSink::stateChanged,
                this, &PlaybackController::on_Sink_State);
        } else {
            m_AudioSink->format().setSampleRate(audio_format.sampleRate());
            m_AudioSink->format().setSampleFormat(audio_format.sampleFormat());
        }
        
        m_AudioSink->start(m_AudioSource);
    }
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
