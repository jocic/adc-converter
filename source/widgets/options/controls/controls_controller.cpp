#include <QDebug>
#include <QApplication>
#include <QFile>
#include <QTimer>
#include <QPushButton>
#include <QMessageBox>

#include "app/app_mediator.h"
#include "widgets/options/controls/controls_model.h"
#include "widgets/options/controls/controls_controller.h"

ControlsController::ControlsController() {
    
    // Processor
    
    m_Processor = new QTimer();
    
    m_Processor->start();
    
    connect(m_Processor, &QTimer::timeout,
        this, &ControlsController::on_Queue_Process);
    
    // Samples
    
    m_Samples = new QQueue<qint64>();
}

void ControlsController::on_View_Initialized(ElementManager* manager) {
    
    QPushButton* btn_sim = (QPushButton*)manager
        ->get(ControlsModel::FIELD_SIMULATE);
    
    connect(btn_sim, &QPushButton::clicked,
        this, &ControlsController::on_Clicked_Simulate);
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
    
    // Does nothing...
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
    
    emit ControlsController::sig_Mediator_Notify("stream_started", {});
    emit ControlsController::sig_Mediator_Notify("new_stream", {});
    
    btn_con->setEnabled(false);
    btn_ref->setEnabled(false);
    btn_sim->setEnabled(false);
    
    quint16 sample;
    
    for (quint64 i = 1; i < sim_data.size(); i+=2) {
        
        sample = 0;
        
        sample |= ((sim_data[i    ] & 0xFF) << 8);
        sample |= ((sim_data[i - 1] & 0xFF)     );
        
        m_Samples->enqueue(sample);
    }
    
    m_Simulating = true;
}

void ControlsController::on_Queue_Process() {
    
    if (m_Simulating) {
        
        qint16 sample = m_Samples->dequeue();
        
        emit ControlsController::sig_Mediator_Notify("new_sample", {
             { "value", QString::asprintf("%d", sample) }
        });
        
        if (m_Samples->size() == 0) {
            
            ElementManager* manager = this->get_View()->get_ElementManager();
            
            QPushButton* btn_con = (QPushButton*)manager
                ->get(ControlsModel::FIELD_CONNECT);
            
            QPushButton* btn_ref = (QPushButton*)manager
                ->get(ControlsModel::FIELD_REFRESH);
            
            QPushButton* btn_sim = (QPushButton*)manager
                ->get(ControlsModel::FIELD_SIMULATE);
            
            m_Simulating = false;
            
            btn_con->setEnabled(true);
            btn_ref->setEnabled(true);
            btn_sim->setEnabled(true);
            
            emit ControlsController::sig_Mediator_Notify("stream_ended", {});
        }
    }
}
