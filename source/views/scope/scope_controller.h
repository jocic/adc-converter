#ifndef ADC_VIEWS_SCOPE_CONTROLLER_H

#define ADC_VIEWS_SCOPE_CONTROLLER_H

#include "app/mvc/abstract_controller.h"

class ScopeController : public AbstractController {
    
    private:
        quint8 m_BitsPerSample;
        bool   m_SamplesSigned;
    
    public slots:
        void on_View_Initialized(ElementManager* manager) override;
        void on_View_Changed() override;
        void on_Model_Changed(QString key, QString value) override;
        void on_Model_Cleared() override;
        void on_Broadcast(quint64 ch, app_data_t data) override;
};

#endif
