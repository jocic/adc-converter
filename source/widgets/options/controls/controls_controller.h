#ifndef ADC_WIDGETS_CONTROLS_CONTROLLER_H

#define ADC_WIDGETS_CONTROLS_CONTROLLER_H

#include <QQueue>
#include <QByteArray>
#include <QTimer>
#include "app/mvc/abstract_controller.h"

class ControlsController : public AbstractController {
    
    private:
        QString m_ComPort;
        QString m_ComMode;
    
    public slots:
        void on_View_Initialized(ElementManager* manager) override;
        void on_View_Changed() override;
        void on_Model_Changed(QString key, QString value) override;
        void on_Model_Cleared() override;
        void on_Mediator_Notify(QString topic, QMap<QString,QString> params) override;
        void on_Processor_Start();
        void on_Processor_End();
        void on_Processor_Sample(qint64 sample);
        void on_Clicked_Connect();
        void on_Clicked_Refresh();
        void on_Clicked_Simulate();
};

#endif
