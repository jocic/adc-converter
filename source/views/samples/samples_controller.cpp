#include <QDebug>
#include <QMap>
#include <QPushButton>

//#include "samples_model.h"
#include "samples_controller.h"
#include "file_loader.h"

void SamplesController::on_View_Initialized(ElementManager* manager) {
    
    qDebug() << "1";
    // Does nothing...
    
    qDebug() << this->get_View();
    QPushButton* test = (QPushButton*)this->get_View()->get_ElementManager()->get(":D");
    
    connect(test, &QPushButton::clicked, this, &SamplesController::on_Offset);
}

void SamplesController::on_View_Changed() {
    
    // Does nothing...
}

void SamplesController::on_Model_Changed(QString key, QString value) {
    
    // Does nothing...
}

void SamplesController::on_Model_Cleared() {
    
    
    // Does nothing...
}

void SamplesController::on_Mediator_Notify(QString topic,
    QMap<QString,QString> params) {
    
    qDebug() << ":D" << topic << params;
}

void SamplesController::on_Offset() {
    
    qDebug() << "2";
    FileLoader* loader = FileLoader::get_Instance();
    
    for (int i = 0; i < loader->get_Buffer()->size() && i < 16; i++) {
        qDebug() << loader->get_Buffer()->at(i);
    }
}
