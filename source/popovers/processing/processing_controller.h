#ifndef ADC_POPOVERS_PROCESSING_CONTROLLER_H

#define ADC_POPOVERS_PROCESSING_CONTROLLER_H

#include "mvc/abstract_controller.h"

class ProcessingController : public AbstractController {
    
    public slots:
        void on_View_Initialized(ElementManager* manager) override;
        void on_View_Changed() override;
        void on_Model_Changed(QString key, QString value) override;
        void on_Model_Cleared() override;
};

#endif
