#ifndef ADC_WIDGETS_COMMUNICATION_CONTROLLER_H

#define ADC_WIDGETS_COMMUNICATION_CONTROLLER_H

#include "mvc/abstract_controller.h"

class CommunicationController : public AbstractController {
    
    public slots:
        void on_View_Initialized(ElementManager* manager) override;
        void on_View_Changed() override;
        void on_Model_Changed(QString key, QString value) override;
        void on_Model_Cleared() override;
        void on_Mediator_Notify(QString topic, QMap<QString,QString> params) override;
};

#endif
