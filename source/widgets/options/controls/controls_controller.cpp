#include <QDebug>
#include <QApplication>
#include <QFile>
#include <QTimer>
#include <QPushButton>
#include <QTextStream>
#include <QMessageBox>

#include "app/app_core.h"
#include "widgets/options/controls/controls_model.h"
#include "widgets/options/controls/controls_controller.h"

void ControlsController::on_View_Initialized(ElementManager* manager) {
    
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

void ControlsController::on_Mediator_Notify(QString topic,
    QMap<QString,QString> params) {
    
    if (topic == "com_data") {
        
        if (params.contains("port")) {
            m_ComPort = params["port"];
        }
    }
}

void ControlsController::on_Clicked_Connect() {
    
    DataReceiver*  data_receiver  = AppCore::get_Instance()->get_DataReceiver();
    TextProcessor* text_processor = AppCore::get_Instance()->get_TextProcessor();
    
    if (!data_receiver->isRunning()) {
        
        emit ControlsController::sig_Mediator_Notify("refresh_ports", {});
        
        text_processor->start();
        
        data_receiver->serialPort()->setPortName(m_ComPort);
        data_receiver->start();
    }
    else {
        
        data_receiver->stop();
        text_processor->stop();
    }
}

void ControlsController::on_Clicked_Refresh() {
    
    emit ControlsController::sig_Mediator_Notify("refresh_ports", {});
}

void ControlsController::on_Clicked_Simulate() {
    
    // Get UI Elements
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QPushButton* btn_con = (QPushButton*)manager
        ->get(ControlsModel::FIELD_CONNECT);
    
    QPushButton* btn_ref = (QPushButton*)manager
        ->get(ControlsModel::FIELD_REFRESH);
    
    QPushButton* btn_sim = (QPushButton*)manager
        ->get(ControlsModel::FIELD_SIMULATE);
    
    // Load Sim Data
    
    QFile sim_file;
    
    sim_file.setFileName("./sim.dat");
    sim_file.open(QFile::OpenModeFlag::ReadOnly);
    
    if (!sim_file.isOpen()) {
        QMessageBox error;
        error.setWindowTitle("App Error");
        error.setText("Simulation data is missing.");
        error.exec();
        return;
    }
    
    QByteArray sim_data = sim_file.readAll();
    
    // Set Field Values
    
    emit ControlsController::sig_Mediator_Notify("stream_params", {
        { "sample_rate", "8500" },
        { "bits_per_sample", "16" },
        { "signed_samples", "true" },
        { "positive_reference", "3300" },
        { "negative_reference", "0" }
    });
    
    // Start Streaming Simulation
    
    AppCore* app_core = AppCore::get_Instance();
    
    emit ControlsController::sig_Mediator_Notify("stream_started", {});
    emit ControlsController::sig_Mediator_Notify("new_stream", {});
    
    app_core->get_Buffer()->clear();
    
    btn_con->setEnabled(false);
    btn_ref->setEnabled(false);
    btn_sim->setEnabled(false);
}

void ControlsController::on_Processor_Start() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QPushButton* btn_con = (QPushButton*)manager
        ->get(ControlsModel::FIELD_CONNECT);
    
    QPushButton* btn_ref = (QPushButton*)manager
        ->get(ControlsModel::FIELD_REFRESH);
    
    QPushButton* btn_sim = (QPushButton*)manager
        ->get(ControlsModel::FIELD_SIMULATE);
    
    btn_con->setText("Disconnect");
    
    btn_con->setEnabled(true);
    btn_ref->setEnabled(false);
    btn_sim->setEnabled(false);
    
    emit ControlsController::sig_Mediator_Notify("stream_started", {});
    emit ControlsController::sig_Mediator_Notify("new_stream", {});
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
    
    emit ControlsController::sig_Mediator_Notify("stream_ended", {});
}

void ControlsController::on_Processor_Sample(qint64 sample) {
    
    emit ControlsController::sig_Mediator_Notify("new_sample", {
         { "value", QString::asprintf("%lld", sample) }
    });
}
