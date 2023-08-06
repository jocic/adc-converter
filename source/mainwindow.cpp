#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "workers/load_worker.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
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
}

MainWindow::~MainWindow()
{
    delete ui;
}


#include "popovers/processing/processing_popover.h"
#include "app_icons.h"
void MainWindow::on_action_Load_triggered()
{
    ProcessingPopover* test = new ProcessingPopover();
    test->initialize();
    test->setWindowTitle("Test Title");
    test->setWindowIcon(*AppIcons::PLAY);
    test->setModal(true);
    test->setVisible(true);
}

