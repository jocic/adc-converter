#ifndef ADC_INFO_GEN_CONTROLLER

#define ADC_INFO_GEN_CONTROLLER

#include "mvc/abstract_controller.h"

class GenController : public AbstractController {
    
    public slots:
        void on_View_Initialized(ElementManager* manager) override;
        void on_View_Changed() override;
        void on_Model_Changed(QString key, QString value) override;
        void on_Model_Cleared() override;
};

#endif
