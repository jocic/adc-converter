#include <QApplication>
#include <QByteArray>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "app/app_mediator.h"
#include "app/app_loader.h"
#include "app/app_saver.h"
#include "app/app_exporter.h"

#include "widgets/options/stream/stream_model.h"

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
    
    mediator->add_Provider(ui->wd_Options_STR->controller(), "wd_stream_data");
    mediator->add_Provider(ui->tab_Samples->controller(), "tab_window_data");
    
    mediator->add_Consumer(ui->tab_Samples->controller(), "wd_stream_data");
    mediator->add_Consumer(ui->wd_Tools_PL->controller(), "wd_stream_data");
    mediator->add_Consumer(ui->wd_Info_GEN->controller(), "wd_stream_data");
    mediator->add_Consumer(ui->tab_Scope->controller(), "tab_window_data");
    
    mediator->add_Consumer(ui->wd_Tools_HEX->controller(), "hex_selected");
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_action_Save_triggered() {
    
    QString dump_filename = "dump_" +
        QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".dat";
    
    // Show Dialog
    
    AppLoader* loader = AppLoader::get_Instance();
    AppSaver*  saver  = AppSaver::get_Instance();
    
    saver->selectFile(dump_filename);
    saver->exec();
    
    if (saver->is_Selected()) {
        saver->process(loader->get_Buffer());
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
    
    AppLoader*   loader   = AppLoader::get_Instance();
    AppExporter* exporter = AppExporter::get_Instance();
    
    exporter->selectFile(export_filename);
    exporter->exec();
    
    if (exporter->is_Selected()) {
        exporter->process(loader->get_Buffer(), sample_rate, bits_per_sample);
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
}
