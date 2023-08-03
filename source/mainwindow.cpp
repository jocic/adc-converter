#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Options
    
    ui->wd_Options_SMP->initialize();
    ui->wd_Options_REF->initialize();
    ui->wd_Options_SER->initialize();
    ui->wd_Options_COM->initialize();
    
    // Tools
    
    ui->wd_Tools_PL->initialize();
    ui->wd_Tools_HEX->initialize();
    ui->wd_Tools_DEC->initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

