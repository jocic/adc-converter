#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Options
    
    ui->wd_Options_BPS->initialize();
    ui->wd_Options_SR->initialize();
    ui->wd_Options_REF->initialize();
    
    // Tools
    
    ui->wd_Tools_PL->initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

