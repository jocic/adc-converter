#include <QDebug>
#include <QByteArray>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>

#include <format.h>

#include "playback_model.h"
#include "playback_view.h"
#include "playback_controller.h"
#include "app/app_loader.h"

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
    
    WAV_FILE    export_wav;
    QFileDialog export_dialog;
    QString     export_filename;
    quint8      export_bytes;
    
    export_filename = "export_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".wav";
    
    export_dialog.setWindowTitle("Export Audio");
    export_dialog.setAcceptMode(QFileDialog::AcceptSave);
    export_dialog.selectFile(export_filename);
    export_dialog.exec();
    
    if (export_dialog.result() == 0) { // Cancelled
        return;
    }
    
    if (export_dialog.selectedFiles().size() == 0) {
        QMessageBox* alert = new QMessageBox();
        alert->setWindowTitle("I/O Warning");
        alert->setText("You haven't selected a file.");
        alert->exec();
        return;
    }
    
    QString export_file_path = export_dialog.selectedFiles().front();
    
    export_wav   = wav_open(export_file_path.toStdString().c_str(), WAV_NEW);
    export_bytes = m_BitsPerSample / 8;
    
    if (!wav_is_open(&export_wav)) {
        QMessageBox* alert = new QMessageBox();
        alert->setWindowTitle("I/O Error");
        alert->setText("File couldn't be generated.");
        alert->exec();
        return;
    }
    
    wav_set_defaults(&export_wav, 1);
    wav_set_SampleRate(&export_wav, m_SampleRate);
    wav_set_BitsPerSample(&export_wav, m_BitsPerSample);
    
    QByteArray* buffer = AppLoader::get_Instance()->get_Buffer();
    
    WAV_PCM32 sample = 0;
    
    quint8 ctl = export_bytes;
    
    for (const auto& byte : *buffer) {
        
        sample <<= 8;
        sample  |= byte;
        
        if (--ctl == 0) {
            
            wav_push_sample(&export_wav, &sample, NULL);
            
            sample = 0;
            ctl    = export_bytes;
        }
    }
    
    wav_close(&export_wav);
    
    QMessageBox* alert = new QMessageBox();
    alert->setWindowTitle("App Notice");
    alert->setText("Audio exported.");
    alert->exec();
}
