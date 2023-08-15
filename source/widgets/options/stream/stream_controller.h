#ifndef ADC_WIDGETS_STREAM_CONTROLLER_H

#define ADC_WIDGETS_STREAM_CONTROLLER_H

#include "app/mvc/abstract_controller.h"

class StreamController : public AbstractController {
    
    public slots:
        void on_View_Initialized(ElementManager* manager) override;
        void on_View_Changed() override;
        void on_Model_Changed(QString key, QString value) override;
        void on_Model_Cleared() override;
        void on_Mediator_Notify(QString topic, QMap<QString,QString> params) override;
};

#endif
