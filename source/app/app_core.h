#ifndef ADC_APP_APP_CORE_H

#define ADC_APP_APP_CORE_H

#include <QObject>
#include <QMutex>
#include <QByteArray>
#include <QMap>

class AppCore : public QObject {
    
    Q_OBJECT
    
    private:
        
        static AppCore* M_INSTANCE;
        static QMutex   M_MUTEX;
        
        QByteArray*            m_Buffer;
        QMap<QString,QString>* m_Params;
        
        AppCore();
        AppCore(const AppCore& ref) = delete;
        void operator = (const AppCore& ref) = delete;
        
    public:
        
        static AppCore* get_Instance();
        
        QByteArray* get_Buffer();
        void get_Chunk(QByteArray& buf, quint64 off, quint64 len);
        void save();
        void load();
};

#endif
