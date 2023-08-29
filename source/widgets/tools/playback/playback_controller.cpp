#include <QDebug>
#include <QByteArray>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QSlider>
#include <QPushButton>

#include <QtMultimedia/QAudioFormat>

#include "playback_model.h"
#include "playback_view.h"
#include "playback_controller.h"
#include "app/app_icons.h"
#include "app/app_core.h"
#include "app/app_loader.h"
#include "app/app_exporter.h"

void PlaybackController::on_View_Initialized(ElementManager* manager) {
    
    // Initialize Member Variables
    
    m_Worker        = new PlayWorker();
    m_SampleRate    = 44100;
    m_BitsPerSample = 8;
    
    // Connect Signals/Slots
    
    QSlider* slide_Time = (QSlider*)manager
        ->get(PlaybackModel::FIELD_PLAYBACK_TIME);
    
    QPushButton* btn_toggle = (QPushButton*)manager
        ->get(PlaybackModel::FIELD_TOGGLE);
    
    QPushButton* btn_export = (QPushButton*)manager
        ->get(PlaybackModel::FIELD_EXPORT);
    
    connect(btn_toggle, &QPushButton::clicked,
        this, &PlaybackController::on_Clicked_Toggle);
    
    connect(btn_export, &QPushButton::clicked,
        this, &PlaybackController::on_Clicked_Export);
    
    connect(m_Worker, &PlayWorker::sig_Started,
        this, &PlaybackController::on_Audio_Started);
    
    connect(m_Worker, &PlayWorker::sig_Stopped,
        this, &PlaybackController::on_Audio_Stopped);
    
    connect(m_Worker, &PlayWorker::sig_Update,
        this, &PlaybackController::on_Playback_Update);
}

void PlaybackController::on_View_Changed() {
    
    
}

void PlaybackController::on_Model_Changed(QString key, QString value) {
    
    
}

void PlaybackController::on_Model_Cleared() {
    
    
}

void PlaybackController::on_Mediator_Notify(QString topic,
    QMap<QString,QString> params) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QSlider* slide_Time = (QSlider*)manager
        ->get(PlaybackModel::FIELD_PLAYBACK_TIME);
    
    QPushButton* btn_toggle = (QPushButton*)manager
        ->get(PlaybackModel::FIELD_TOGGLE);
    
    QPushButton* btn_export = (QPushButton*)manager
        ->get(PlaybackModel::FIELD_EXPORT);
    
    if (topic == "stream_started") {
        slide_Time->setEnabled(false);
        btn_toggle->setEnabled(false);
        btn_export->setEnabled(false);
    }
    else if (topic == "stream_ended") {
        slide_Time->setEnabled(true);
        btn_toggle->setEnabled(true);
        btn_export->setEnabled(true);
    }
    
    /// to be refactored
    
    if (topic == "wd_stream_data") {
        
        if (params.contains("txt_SampleRate")) {
            m_SampleRate = params["txt_SampleRate"].toUInt();
        }
        
        if (params.contains("comb_BitsPerSample")) {
            m_BitsPerSample = params["comb_BitsPerSample"].toUInt();
        }
        
        qDebug() << "Received:" << m_SampleRate << m_BitsPerSample;
    }
}

void PlaybackController::on_Playback_Update(qreal time) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QSlider* slide_time = (QSlider*)manager
        ->get(PlaybackModel::FIELD_PLAYBACK_TIME);
    
    qreal duration = m_Worker->get_Source()->get_Duration();
    
    quint64 slide_pos = (time / duration) * slide_time->maximum();
    
    slide_time->setValue(slide_pos);
}

void PlaybackController::on_Audio_Started() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QPushButton* btn_toggle = (QPushButton*)manager
        ->get(PlaybackModel::FIELD_TOGGLE);
    
    btn_toggle->setText("Stop");
    btn_toggle->setIcon(*AppIcons::STOP);
    
    m_Playing = true;
}

void PlaybackController::on_Audio_Stopped() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    // Reset Slider;
    
    QSlider* slide_Time = (QSlider*)manager
        ->get(PlaybackModel::FIELD_PLAYBACK_TIME);
    
    slide_Time->setValue(0);
    
    // Update Toggle
    
    QPushButton* btn_toggle = (QPushButton*)manager
        ->get(PlaybackModel::FIELD_TOGGLE);
    
    btn_toggle->setText("Play");
    btn_toggle->setIcon(*AppIcons::PLAY);
    
    m_Playing = false;
}

void PlaybackController::on_Clicked_Toggle() {
    
    // Check Sample Rate
    
    if (!m_Playing && m_SampleRate < 1000) {
        QMessageBox error;
        error.setWindowTitle("App Error");
        error.setText("Specified sample rate isn't supported.");
        error.exec();
    }
    
    // Start Playback
    
    QAudioFormat* format = m_Worker->get_Format();
    
    format->setSampleRate(m_SampleRate);
    
    switch (m_BitsPerSample) {
        case 8:
            format->setSampleFormat(QAudioFormat::SampleFormat::UInt8);
            break;
        case 16:
            format->setSampleFormat(QAudioFormat::SampleFormat::Int16);
            break;
        case 24:
        case 32:
            format->setSampleFormat(QAudioFormat::SampleFormat::Int32);
            break;
        default: ;
    }
    
    if (m_Playing) {
        m_Worker->stop();
    } else {
        m_Worker->play();
    }
}

void PlaybackController::on_Clicked_Export() {
    
    QString export_filename = "export_" +
        QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".wav";
    
    // Show Dialog
    
    AppCore*     app_core = AppCore::get_Instance();
    AppExporter* exporter = AppExporter::get_Instance();
    
    exporter->selectFile(export_filename);
    exporter->exec();
    
    if (exporter->is_Selected()) {
        exporter->process(app_core->get_Buffer(), m_SampleRate, m_BitsPerSample);
    }
}
