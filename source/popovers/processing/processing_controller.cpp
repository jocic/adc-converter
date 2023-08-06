#include <QDebug>
#include <QProgressBar>

#include "processing_model.h"
#include "processing_controller.h"

void ProcessingController::on_View_Initialized(ElementManager* manager) {
    
    // Does nothing...
}

void ProcessingController::on_View_Changed() {
    
    // Does nothing...
}

void ProcessingController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == ProcessingModel::FIELD_PROGRESS) {
        
        QProgressBar* progress = (QProgressBar*)manager
            ->get(ProcessingModel::FIELD_PROGRESS);
        
        progress->setValue(value.toUInt());
    }
}

void ProcessingController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QProgressBar* progress = (QProgressBar*)manager
        ->get(ProcessingModel::FIELD_PROGRESS);
    
    progress->setValue(0);
}
