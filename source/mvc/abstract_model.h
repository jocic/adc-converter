#ifndef ADC_CORE_ABSTRACT_MODEL

#define ADC_CORE_ABSTRACT_MODEL

#include <QObject>
#include <QMap>

class AbstractModel : public QObject {
    
    Q_OBJECT
    
    private:
        QMap<QString,QString> m_Attributes;
    
    public:
        QString get(QString key);
        void set(QString key, QString value);
        bool exists(QString key);
        void clear();
    
    signals:
         void sig_Model_Updated(QString key, QString value);
         void sig_Model_Cleared();
};

#endif
