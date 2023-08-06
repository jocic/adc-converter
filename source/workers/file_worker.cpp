#include <QLayout>
#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>

#include "file_worker.h"

Popover::Popover() {
    
    this->setWindowTitle("Processing...");
    this->setModal(true);
    
    QVBoxLayout*  lay_main = new QVBoxLayout();
    QLabel*       lbl_msg  = new QLabel();
    QProgressBar* pb_prog  = new QProgressBar();
    
    pb_prog->setFixedWidth(400);
    
    lbl_msg->setText("Your file is being processed, please wait.");
    
    
    QPushButton* btn_ok = new QPushButton("Cancel");
    
    QFrame* line = new QFrame();
    
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    
    lay_main->addWidget(lbl_msg);
    lay_main->addWidget(pb_prog);
    lay_main->addWidget(line);
    lay_main->addWidget(btn_ok);
    
    this->setLayout(lay_main);
}

void FileWorker::start() {
    
    Popover* pop = new Popover();
    
    pop->setVisible(true);
}

void FileWorker::stop() {
    
}

void FileWorker::pause() {
    
}
