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

#endif
