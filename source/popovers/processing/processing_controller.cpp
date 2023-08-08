#include <QDebug>
#include <QDialog>
#include <QProgressBar>
#include <QPushButton>

#include "processing_popover.h"
#include "processing_model.h"
#include "processing_controller.h"

void ProcessingController::on_View_Initialized(ElementManager* manager) {
    
    QPushButton* cancel = (QPushButton*)manager
        ->get(ProcessingModel::FIELD_CANCEL);
    
    ProcessingPopover* popover = (ProcessingPopover*)this->get_Widget();
    
    connect(cancel, &QPushButton::clicked,
      popover, &ProcessingPopover::on_Close);
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

void ProcessingController::on_Mediator_Notify(QString topic,
    QMap<QString,QString> params) {
    
    // Does nothing...
}
