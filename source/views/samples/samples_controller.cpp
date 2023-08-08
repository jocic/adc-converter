#include <QDebug>
#include <QMap>

//#include "samples_model.h"
#include "samples_controller.h"

void SamplesController::on_View_Initialized(ElementManager* manager) {
    
    // Does nothing...
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
