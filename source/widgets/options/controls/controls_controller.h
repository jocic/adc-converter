#ifndef ADC_WIDGETS_CONTROLS_CONTROLLER_H

#define ADC_WIDGETS_CONTROLS_CONTROLLER_H

#include <QQueue>
#include <QByteArray>
#include <QTimer>
#include "app/mvc/abstract_controller.h"

class ControlsController : public AbstractController {
    
    typedef struct tm_duration {
        quint64 minutes;
        quint64 seconds;
        quint64 milliseconds;
    } tm_duration_t;
    
    private:
        QTimer*        m_Timer;
        QString        m_ComPort;
        QString        m_ComMode;
        tm_duration_t* m_Active;
        quint8         m_BitsPerSample;
    
    public slots:
        void on_View_Initialized(ElementManager* manager) override;
        void on_View_Changed() override;
        void on_Model_Changed(QString key, QString value) override;
        void on_Model_Cleared() override;
        void on_Broadcast(quint64 ch, app_data_t data) override;
        void on_Processor_Start();
        void on_Processor_End();
        void on_Processor_Sample(qint64 sample);
        void on_Clicked_Connect();
        void on_Clicked_Refresh();
        void on_Clicked_Simulate();
        void on_Timer_Tick();
};

#endif
