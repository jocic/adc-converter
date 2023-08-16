#include <QApplication>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "app/app_mediator.h"
#include "app/app_loader.h"
#include "app/app_saver.h"

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
    
    // Widgets - Tools
    
    ui->wd_Tools_PL->initialize();
    ui->wd_Tools_HEX->initialize();
    ui->wd_Tools_DEC->initialize();
    
    // Widgets - Info
    
    ui->wd_Info_GEN->initialize();
    
    // Views
    
    ui->tab_Samples->initialize();
    
    ////////////////////////////////////////
    
    AppMediator* mediator = AppMediator::get_Instance();
    AppLoader*  loader   = AppLoader::get_Instance();
    
    mediator->add_Provider(ui->wd_Options_STR->controller(), "wd_stream_data");
    
    mediator->add_Consumer(ui->tab_Samples->controller(), "wd_stream_data");
    mediator->add_Consumer(ui->wd_Tools_PL->controller(), "wd_stream_data");
    mediator->add_Consumer(ui->wd_Info_GEN->controller(), "wd_stream_data");
    
    mediator->add_Consumer(ui->wd_Tools_PL->controller(), "wd_playback_request");
    
    mediator->add_Consumer(ui->wd_Tools_HEX->controller(), "hex_selected");
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_action_Save_triggered() {
    
    AppLoader* loader = AppLoader::get_Instance();
    AppSaver*  saver  = AppSaver::get_Instance();
    
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
    
    QMap<QString,QString> params;
    
    params.insert("request", "export");
    
    emit AppMediator::get_Instance()->sig_Notify("wd_playback_request", params);
    
    return;
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

