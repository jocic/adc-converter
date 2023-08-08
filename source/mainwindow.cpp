#include "mainwindow.h"
#include "./app_mediator.h"
#include "./ui_mainwindow.h"

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
    
    mediator->add_Provider(ui->wd_Options_STR->controller(), "stream_info");
    
    mediator->add_Consumer(ui->tab_Samples->controller(), "stream_info");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Load_triggered()
{    
    FileLoader* loader = FileLoader::get_Instance(); 
    
    QString file_selected = loader->getOpenFileName(this, "Load Samples");
    
    if (!file_selected.isEmpty()) {
        loader->process(file_selected);
    }
}


