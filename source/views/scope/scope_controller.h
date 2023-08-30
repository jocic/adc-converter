#ifndef ADC_VIEWS_SCOPE_CONTROLLER_H

#define ADC_VIEWS_SCOPE_CONTROLLER_H

#include "app/mvc/abstract_controller.h"

class ScopeController : public AbstractController {
    
    public slots:
        void on_View_Initialized(ElementManager* manager) override;
        void on_View_Changed() override;
        void on_Model_Changed(QString key, QString value) override;
        void on_Model_Cleared() override;
        void on_Broadcast(QString topic, QMap<QString,QString> params) override;
        void on_Broadcast_ALT(QString topic, void* params) override;
};

#endif
