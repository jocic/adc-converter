#include <QDebug>
#include <QApplication>
#include <QFile>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QTextStream>
#include <QMessageBox>

#include "app/app_mediator.h"
#include "app/app_core.h"
#include "widgets/options/controls/controls_model.h"
#include "widgets/options/controls/controls_controller.h"

void ControlsController::on_View_Initialized(ElementManager* manager) {
    
    this->tuneTo(AppMediator::Channel::STREAM_PARAMS);
    this->tuneTo(AppMediator::Channel::COMM_PARAMS);
    
    //////////////////////////////
    
    m_Active = new tm_duration_t;
    
    //////////////////////////////
    
    m_Timer = new QTimer();
    
    m_Timer->setTimerType(Qt::TimerType::PreciseTimer);
    m_Timer->setInterval(10);
    
    connect(m_Timer, &QTimer::timeout,
        this, &ControlsController::on_Timer_Tick);
    
    //////////////////////////////
    
    QPushButton* btn_con = (QPushButton*)manager
        ->get(ControlsModel::FIELD_CONNECT);
    
    QPushButton* btn_ref = (QPushButton*)manager
        ->get(ControlsModel::FIELD_REFRESH);
    
    QPushButton* btn_sim = (QPushButton*)manager
        ->get(ControlsModel::FIELD_SIMULATE);
    
    connect(btn_con, &QPushButton::clicked,
        this, &ControlsController::on_Clicked_Connect);
    
    connect(btn_ref, &QPushButton::clicked,
        this, &ControlsController::on_Clicked_Refresh);
    
    connect(btn_sim, &QPushButton::clicked,
        this, &ControlsController::on_Clicked_Simulate);
    
    //////////////////////////////
    
    DataReceiver*  data_receiver  = AppCore::get_Instance()->get_DataReceiver();    
    TextProcessor* text_processor = AppCore::get_Instance()->get_TextProcessor();
    
    connect(data_receiver, &DataReceiver::sig_Started,
        this, &ControlsController::on_Processor_Start);
    
    connect(data_receiver, &DataReceiver::sig_Stopped,
        this, &ControlsController::on_Processor_End);
    
    connect(data_receiver, &DataReceiver::sig_BufferRead,
        text_processor, &TextProcessor::on_NewData);
    
    connect(text_processor, &TextProcessor::sig_NewSample,
        this, &ControlsController::on_Processor_Sample);
}

void ControlsController::on_View_Changed() {
    
    // Does nothing...
}

void ControlsController::on_Model_Changed(QString key, QString value) {
    
    // Does nothing...
}

void ControlsController::on_Model_Cleared() {
    
    // Does nothing...
}

void ControlsController::on_Broadcast(quint64 ch, app_data_t data) {
    
    if (ch == AppMediator::Channel::COMM_PARAMS) {
        m_ComPort = data.com_config.com_port;
    }
}

void ControlsController::on_Clicked_Connect() {
    
    DataReceiver*  data_receiver  = AppCore::get_Instance()->get_DataReceiver();
    TextProcessor* text_processor = AppCore::get_Instance()->get_TextProcessor();
    
    if (!data_receiver->isRunning()) {
        
        app_data_t data;
        
        data.event  = "refresh_ports";
        data.params = {};
        
        emit ControlsController::sig_Broadcast(
            AppMediator::Channel::APP_EVENTS, data);
        
        text_processor->start();
        
        data_receiver->serialPort()->setPortName(m_ComPort);
        data_receiver->start();
    }
    else {
        
        text_processor->stop();
        data_receiver->stop();
    }
}

void ControlsController::on_Clicked_Refresh() {
    
    app_data_t data;
    
    data.event  = "refresh_ports";
    data.params = {};
    
    emit ControlsController::sig_Broadcast(
        AppMediator::Channel::APP_EVENTS, data);
}

void ControlsController::on_Clicked_Simulate() {
    
//    emit ControlsController::sig_Broadcast("stream_params", {
//        { "sample_rate", "10000" },
//        { "bits_per_sample", "16" },
//        { "signed_samples", "true" },
//        { "positive_reference", "3300" },
//        { "negative_reference", "0" }
//    });
    
    DataReceiver*  data_receiver  = AppCore::get_Instance()->get_DataReceiver();
    TextProcessor* text_processor = AppCore::get_Instance()->get_TextProcessor();
    
    if (!data_receiver->isRunning()) {
        
        text_processor->start();
        data_receiver->start(true);
    }
    else {
        
        text_processor->stop();
        data_receiver->stop();
    }
}

void ControlsController::on_Processor_Start() {
    
    AppCore* app_core = AppCore::get_Instance();
    
    app_core->get_Buffer()->clear();
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QPushButton* btn_con = (QPushButton*)manager
        ->get(ControlsModel::FIELD_CONNECT);
    
    QPushButton* btn_ref = (QPushButton*)manager
        ->get(ControlsModel::FIELD_REFRESH);
    
    QPushButton* btn_sim = (QPushButton*)manager
        ->get(ControlsModel::FIELD_SIMULATE);
    
    QLabel* lbl_active = (QLabel*)manager
        ->get(ControlsModel::FIELD_ACTIVE);
    
    btn_con->setText("Disconnect");
    lbl_active->setText("00:00:00");
    
    btn_con->setEnabled(true);
    btn_ref->setEnabled(false);
    btn_sim->setEnabled(false);
    
    app_data_t data;
    
    data.event  = "stream_started";
    data.params = {};
    
    emit ControlsController::sig_Broadcast(
        AppMediator::Channel::STREAM_EVENTS, data);
    
    data.event  = "new_stream";
    data.params = {};
    
    emit ControlsController::sig_Broadcast(
        AppMediator::Channel::STREAM_EVENTS, data);
    
    m_Active->minutes = m_Active->seconds = m_Active->milliseconds = 0;
    
    m_Timer->start();
}

void ControlsController::on_Processor_End() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QPushButton* btn_con = (QPushButton*)manager
        ->get(ControlsModel::FIELD_CONNECT);
    
    QPushButton* btn_ref = (QPushButton*)manager
        ->get(ControlsModel::FIELD_REFRESH);
    
    QPushButton* btn_sim = (QPushButton*)manager
        ->get(ControlsModel::FIELD_SIMULATE);
    
    btn_con->setText("Connect");
    
    btn_con->setEnabled(true);
    btn_ref->setEnabled(true);
    btn_sim->setEnabled(true);
    
    app_data_t data;
    
    data.event  = "stream_ended";
    data.params = {};
    
    emit ControlsController::sig_Broadcast(
        AppMediator::Channel::STREAM_EVENTS, data);
    
    m_Timer->stop();
}

void ControlsController::on_Processor_Sample(qint64 sample) {
    
    QByteArray* data_buffer = AppCore::get_Instance()->get_Buffer();
    
    data_buffer->push_back((sample >> 0) & 0xFF);
    data_buffer->push_back((sample >> 8) & 0xFF);
    
    app_data_t data;
    
    data.event     = "new_sample";
    data.value.i64 = sample;
    
    emit ControlsController::sig_Broadcast(
        AppMediator::Channel::STREAM_EVENTS, data);
}

void ControlsController::on_Timer_Tick() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QLabel* lbl_active = (QLabel*)manager->get(ControlsModel::FIELD_ACTIVE);
    
    if (m_Timer->isActive()) {
        
        if (++m_Active->milliseconds == 100) {
            m_Active->seconds     += 1;
            m_Active->milliseconds = 0;
        }
        
        if (m_Active->seconds == 60) {
            m_Active->minutes += 1;
            m_Active->seconds  = 0;
        }
        
        QString str_active = QString::asprintf("%02lld:%02lld:%02lld",
            m_Active->minutes, m_Active->seconds, m_Active->milliseconds);
        
        lbl_active->setText(str_active);
    }
}
