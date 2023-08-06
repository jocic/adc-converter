#ifndef ADC_WRK_FILE_WORKER_H

#define ADC_WRK_FILE_WORKER_H

#include <QObject>
#include <QDialog>
#include <QThread>

class Popover : public QDialog {
    
    public:
        Popover();
};

class Worker : public QThread {
    public:
        void run() override;
};

class FileWorker : public QObject {
    
    Q_OBJECT
    
    private:
        
        Worker*  m_Worker;
        Popover* m_Popover;
    
    public:
        void start();
        void stop();
        void pause();
};
#include "popovers/processing/processing_model.h"
class TestWorker : public QThread {

Q_OBJECT
public:
    ProcessingModel* model;
    void run() override {
       int curr = 0; 
        while (true) {
            
            curr++;
            
            if (curr >= 100) {
                curr = 0;
            }
            qDebug() << "?";
            this->msleep(25);
            
            model->set_Progress(curr);
        }
    }
};    

#endif
