#include <QApplication>
#include <QByteArray>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "app/app_mediator.h"
#include "app/app_core.h"
#include "app/app_loader.h"
#include "app/app_saver.h"
#include "app/app_exporter.h"
#include "app/app_types.h"
#include "app/workers/load_worker.h"

#include "widgets/options/stream/stream_model.h"

#include "popovers/about/about_popover.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    ////////////////////////////////////////
    
    // Widgets - Options
    
    ui->wd_Options_STR->initialize();
    ui->wd_Options_REF->initialize();
    ui->wd_Options_SER->initialize();
    ui->wd_Options_COM->initialize();
    ui->wd_Options_CTL->initialize();
    
    // Widgets - Tools
    
    ui->wd_Tools_PL->initialize();
    ui->wd_Tools_HEX->initialize();
    ui->wd_Tools_DEC->initialize();
    
    // Widgets - Info
    
    ui->wd_Info_GEN->initialize();
    
    // Views
    
    ui->tab_Scope->initialize();
    ui->tab_Samples->initialize();
    
    ////////////////////////////////////////
    
    AppMediator* mediator = AppMediator::get_Instance();
    AppLoader*   loader   = AppLoader::get_Instance();
    
    // General
    
    connect(loader->get_Worker(), &LoadWorker::sig_Done,
        this, &MainWindow::on_Dump_Loaded);
    
    connect(mediator, &AppMediator::sig_Broadcast,
        this, &MainWindow::on_Broadcast);
    
    // Providers
    
    mediator->reg_Transmitter(ui->wd_Options_CTL
        ->controller(),AppMediator::Channel::STREAM_EVENTS);
    mediator->reg_Transmitter(ui->wd_Options_CTL
        ->controller(), AppMediator::Channel::STREAM_PARAMS);
    mediator->reg_Transmitter(ui->wd_Options_CTL
        ->controller(), AppMediator::Channel::APP_REQUESTS);
    mediator->reg_Transmitter(ui->wd_Options_COM
        ->controller(), AppMediator::Channel::COMM_PARAMS);
    mediator->reg_Transmitter(ui->wd_Options_STR
        ->controller(), AppMediator::Channel::STREAM_PARAMS);
    mediator->reg_Transmitter(ui->wd_Options_SER
        ->controller(), AppMediator::Channel::SERIAL_PARAMS);
    mediator->reg_Transmitter(ui->wd_Options_REF
        ->controller(), AppMediator::Channel::REFERENCE_PARAMS);
    mediator->reg_Transmitter(ui->tab_Samples
        ->controller(), AppMediator::Channel::SCOPE_DATA);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_Broadcast(int ch, app_data_t data) {
    
    if (ch == AppMediator::Channel::STREAM_EVENTS) {
        
        if (data.event == "stream_started") {
            ui->action_Save->setEnabled(false);
            ui->action_Load->setEnabled(false);
            ui->action_Export->setEnabled(false);
        }
        else if (data.event == "stream_ended") {
            ui->action_Save->setEnabled(true);
            ui->action_Load->setEnabled(true);
            ui->action_Export->setEnabled(true);
        }
    }
}

void MainWindow::on_Dump_Loaded() {
    
    AppMediator* app_mediator = AppMediator::get_Instance();
    AppCore*     app_core     = AppCore::get_Instance();
    AppLoader*   app_loader   = AppLoader::get_Instance(); 
    
    app_core->get_Buffer()->clear();
    app_core->get_Buffer()->append(*app_loader->get_Buffer());
    
    /////////////////////////////
    
    app_data_t data = { .event = "dump_loaded" };
    
    app_mediator->on_Broadcast(AppMediator::Channel::APP_EVENTS, data);
}

void MainWindow::on_action_Save_triggered() {
    
    QString dump_filename = "dump_" +
        QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".dat";
    
    // Show Dialog
    
    AppCore*  app_core = AppCore::get_Instance();
    AppSaver* saver    = AppSaver::get_Instance();
    
    saver->selectFile(dump_filename);
    saver->exec();
    
    if (saver->is_Selected()) {
        saver->process(app_core->get_Buffer());
    }
}

void MainWindow::on_action_Load_triggered() {
     
    AppLoader* loader = AppLoader::get_Instance(); 
    
    loader->exec();
    
    if (loader->is_Selected()) {
        loader->process();
    }
}

void MainWindow::on_action_Export_triggered() {
    
    QString export_filename = "export_" +
        QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".wav";
    
    // Get Stream Data
    
    StreamModel* model  = (StreamModel*)ui->wd_Options_STR->model();
    
    quint64 sample_rate     = model->get_SampleRate();
    quint8  bits_per_sample = model->get_BitsPerSample();
    
    // Show Dialog
    
    AppCore*     app_core = AppCore::get_Instance();
    AppExporter* exporter = AppExporter::get_Instance();
    
    exporter->selectFile(export_filename);
    exporter->exec();
    
    if (exporter->is_Selected()) {
        exporter->process(app_core->get_Buffer(), sample_rate, bits_per_sample);
    }
}

void MainWindow::on_action_Exit_triggered() {
    
    QApplication::exit(0);
}

void MainWindow::on_action_Scope_triggered() {
    
    quint8 tab_index = ui->tab_General->indexOf(ui->tab_Scope);
    
    if (ui->action_Scope->isChecked()) {
        ui->tab_General->addTab(ui->tab_Scope, "Scope");
        tab_index = ui->tab_General->indexOf(ui->tab_Scope);
        ui->tab_General->setCurrentIndex(tab_index);
    } else {
        ui->tab_General->removeTab(tab_index);
    }
}

void MainWindow::on_action_Samples_triggered() {
    
    quint8 tab_index = ui->tab_General->indexOf(ui->tab_Samples);
    
    if (ui->action_Samples->isChecked()) {
        ui->tab_General->addTab(ui->tab_Samples, "Samples");
        tab_index = ui->tab_General->indexOf(ui->tab_Samples);
        ui->tab_General->setCurrentIndex(tab_index);
    } else {
        ui->tab_General->removeTab(tab_index);
    }
}

void MainWindow::on_action_Options_triggered() {
    
    if (ui->action_Options->isChecked()) {
        this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, ui->dock_Options);
        ui->dock_Options->setVisible(true);
    } else {
        this->removeDockWidget(ui->dock_Options);
    }
}

void MainWindow::on_action_Tools_triggered() {
    
    if (ui->action_Tools->isChecked()) {
        this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, ui->dock_Tools);
        ui->dock_Tools->setVisible(true);
    } else {
        this->removeDockWidget(ui->dock_Tools);
    }
}

void MainWindow::on_action_Info_triggered() {
    
    if (ui->action_Info->isChecked()) {
        this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, ui->dock_Info);
        ui->dock_Info->setVisible(true);
    } else {
        this->removeDockWidget(ui->dock_Info);
    }
}

void MainWindow::on_action_FullScreen_triggered() {
    
    if (this->isFullScreen()) {
        this->showNormal();
    } else {
        this->showFullScreen();
    }
}

void MainWindow::on_action_AlwaysOnTop_triggered() {
    
    Qt::WindowFlags flags = this->windowFlags();
    
    if (ui->action_AlwaysOnTop->isChecked()) {
        flags |= Qt:: WindowStaysOnTopHint;
    } else {
        flags &= Qt:: WindowStaysOnTopHint;
    }
    
    this->hide();
    this->setWindowFlags(flags);
    
    QThread::msleep(250);
    
    this->show();
}

void MainWindow::on_action_DefaultView_triggered() {
    
    // Views
    
    qint8 tab_scope   = ui->tab_General->indexOf(ui->tab_Scope);
    qint8 tab_samples = ui->tab_General->indexOf(ui->tab_Samples);
    
    ui->tab_General->clear();
    
    ui->tab_General->addTab(ui->tab_Scope, "Scope");
    ui->tab_General->addTab(ui->tab_Samples, "Samples");
    
    ui->action_Scope->setChecked(true);
    ui->action_Samples->setChecked(true);
    
    // Dock Widgets
    
    this->removeDockWidget(ui->dock_Options);
    this->removeDockWidget(ui->dock_Tools);
    this->removeDockWidget(ui->dock_Info);
    
    this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, ui->dock_Options);    
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, ui->dock_Tools);    
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, ui->dock_Info);
    
    ui->dock_Options->setFloating(false);
    ui->dock_Tools->setFloating(false);
    ui->dock_Info->setFloating(false);
    
    ui->dock_Options->setVisible(true);
    ui->dock_Tools->setVisible(true);
    ui->dock_Info->setVisible(true);
    
    ui->action_Options->setChecked(true);
    ui->action_Tools->setChecked(true);
    ui->action_Info->setChecked(true);
    
    this->resizeDocks({
        ui->dock_Options,
        ui->dock_Tools,
        ui->dock_Info,
    }, {
        270,
        270,
        270
    }, Qt::Orientation::Horizontal);
}

void MainWindow::on_action_CompactView_triggered() {
    
    // Views
    
    qint8 tab_scope   = ui->tab_General->indexOf(ui->tab_Scope);
    qint8 tab_samples = ui->tab_General->indexOf(ui->tab_Samples);
    
    ui->tab_General->clear();
    
    ui->tab_General->addTab(ui->tab_Scope, "Scope");
    ui->tab_General->addTab(ui->tab_Samples, "Samples");
    
    ui->action_Scope->setChecked(true);
    ui->action_Samples->setChecked(true);
    
    // Dock Widgets
    
    this->removeDockWidget(ui->dock_Options);
    this->removeDockWidget(ui->dock_Tools);
    this->removeDockWidget(ui->dock_Info);
    
    this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, ui->dock_Options);    
    this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, ui->dock_Tools);    
    this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, ui->dock_Info);
    
    ui->dock_Options->setFloating(false);
    ui->dock_Tools->setFloating(false);
    ui->dock_Info->setFloating(false);
    
    this->tabifyDockWidget(ui->dock_Options, ui->dock_Tools);
    this->tabifyDockWidget(ui->dock_Options, ui->dock_Info);
    
    ui->dock_Options->setVisible(true);
    ui->dock_Tools->setVisible(true);
    ui->dock_Info->setVisible(true);
    
    ui->action_Options->setChecked(true);
    ui->action_Tools->setChecked(true);
    ui->action_Info->setChecked(true);
    
    this->resizeDocks({
        ui->dock_Options,
        ui->dock_Tools,
        ui->dock_Info,
    }, {
        270,
        270,
        270
    }, Qt::Orientation::Horizontal);
}

void MainWindow::on_action_About_triggered() {
    
    AboutPopover* about = new AboutPopover(this);
    
    about->initialize();
    about->exec();
    
    delete about;
}

