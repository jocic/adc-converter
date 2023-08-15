#ifndef ADC_POPOVERS_PROCESSING_CONTROLLER_H

#define ADC_POPOVERS_PROCESSING_CONTROLLER_H

#include "app/mvc/abstract_controller.h"

class ProcessingController : public AbstractController {
    
    Q_OBJECT
    
    public slots:
        void on_View_Initialized(ElementManager* manager) override;
        void on_View_Changed() override;
        void on_Model_Changed(QString key, QString value) override;
        void on_Model_Cleared() override;
        void on_Mediator_Notify(QString topic, QMap<QString,QString> params) override;
};

#endif
