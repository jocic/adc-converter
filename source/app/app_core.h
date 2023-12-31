#ifndef ADC_APP_APP_CORE_H

#define ADC_APP_APP_CORE_H

#include <QObject>
#include <QMutex>
#include <QByteArray>
#include <QMap>

#include "app/data/data_receiver.h"
#include "app/data/text_processor.h"
#include "app/data/binary_processor.h"

class AppCore : public QObject {
    
    Q_OBJECT
    
    private:
        
        static AppCore* M_INSTANCE;
        static QMutex   M_MUTEX;
        
        QByteArray*            m_Buffer;
        QMap<QString,QString>* m_Params;
        
        DataReceiver*    m_DataReceiver;
        TextProcessor*   m_TextProcessor;
        BinaryProcessor* m_BinaryProcessor;
        
        AppCore();
        AppCore(const AppCore& ref) = delete;
        void operator = (const AppCore& ref) = delete;
        
    public:
        
        static AppCore* get_Instance();
        
        QByteArray* get_Buffer();
        DataReceiver* get_DataReceiver();
        TextProcessor* get_TextProcessor();
        BinaryProcessor* get_BinaryProcessor();
        void get_Chunk(QByteArray& buf, quint64 off, quint64 len);
        void save();
        void load();
};

#endif
