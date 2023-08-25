#ifndef ADC_WIDGETS_CONTROLS_CONTROLLER_H

#define ADC_WIDGETS_CONTROLS_CONTROLLER_H

#include <QQueue>
#include <QByteArray>
#include <QTimer>
#include "app/mvc/abstract_controller.h"
#include "app/workers/data_worker.h"

class ControlsController : public AbstractController {
    
    private:
        
        DataWorker*      m_DataWorker;
        QTimer*          m_Processor;
        QQueue<qint64>*  m_Samples;
        
        QString m_ComPort;
        QString m_ComMode;
        
        bool             m_Streaming;
        bool             m_Simulating;
        
    public:
         ControlsController();
    
    public slots:
        void on_View_Initialized(ElementManager* manager) override;
        void on_View_Changed() override;
        void on_Model_Changed(QString key, QString value) override;
        void on_Model_Cleared() override;
        void on_Mediator_Notify(QString topic, QMap<QString,QString> params) override;
        void on_Clicked_Connect();
        void on_Clicked_Refresh();
        void on_Clicked_Simulate();
        void on_Processor_Start();
        void on_Processor_End();
        void on_Processor_Read(QByteArray buffer);
        void on_Queue_Process();
};

#endif
