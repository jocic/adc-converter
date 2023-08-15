#ifndef ADC_MVC_ABSTRACT_MODEL_H

#define ADC_MVC_ABSTRACT_MODEL_H

#include <QObject>
#include <QMap>

class AbstractModel : public QObject {
    
    Q_OBJECT
    
    private:
        QMap<QString,QString> m_Attributes;
    
    public:
        QString get(QString key);
        void set(QString key, QString value, bool silent = false);
        bool exists(QString key);
        void clear();
    
    signals:
         void sig_Model_Updated(QString key, QString value);
         void sig_Model_Cleared();
};

#endif
