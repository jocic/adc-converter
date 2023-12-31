#ifndef ADC_VIEWS_SAMPLES_CONTROLLER_H

#define ADC_VIEWS_SAMPLES_CONTROLLER_H

#include "app/mvc/abstract_controller.h"

class SamplesController : public AbstractController {
    
    public slots:
        void on_View_Initialized(ElementManager* manager) override;
        void on_View_Changed() override;
        void on_Model_Changed(QString key, QString value) override;
        void on_Model_Cleared() override;
        void on_Broadcast(quint64 ch, app_data_t data) override;
        void on_Data_Loaded();
        void on_Clicked_Offset();
        void on_Clicked_Prev();
        void on_Clicked_Next();
};

#endif
