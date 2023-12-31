#ifndef ADC_WIDGETS_GENERAL_CONTROLLER_H

#define ADC_WIDGETS_GENERAL_CONTROLLER_H

#include "app/mvc/abstract_controller.h"

class GeneralController : public AbstractController {
    
    private:
        quint64 m_SampleRate    = 44100;
        quint8  m_BitsPerSample = 8;
    
    public slots:
        void on_View_Initialized(ElementManager* manager) override;
        void on_View_Changed() override;
        void on_Model_Changed(QString key, QString value) override;
        void on_Model_Cleared() override;
        void on_Broadcast(quint64 ch, app_data_t data) override;
        void on_Data_Loaded();
};

#endif
