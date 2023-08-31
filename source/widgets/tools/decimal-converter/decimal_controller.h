#ifndef ADC_WIDGETS_DECIMAL_CONTROLLER_H

#define ADC_WIDGETS_DECIMAL_CONTROLLER_H

#include "app/mvc/abstract_controller.h"

class DecimalController : public AbstractController {
    
    public slots:
        void on_View_Initialized(ElementManager* manager) override;
        void on_View_Changed() override;
        void on_Model_Changed(QString key, QString value) override;
        void on_Model_Cleared() override;
        void on_Broadcast(quint64 ch, app_data_t data) override;
};

#endif
