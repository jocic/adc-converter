#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    ui->wd_Options_BPS->initialize();
    ui->wd_Options_SR->initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

