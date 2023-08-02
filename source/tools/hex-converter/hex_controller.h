#ifndef ADC_TOOLS_HEX_CONTROLLER

#define ADC_TOOLS_HEX_CONTROLLER

#include "mvc/abstract_controller.h"

class HexController : public AbstractController {
    
    public slots:
        void on_View_Initialized(ElementManager* manager) override;
        void on_View_Changed() override;
        void on_Model_Changed(QString key, QString value) override;
        void on_Model_Cleared() override;
};

#endif
