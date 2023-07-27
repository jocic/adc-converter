#ifndef ELEMENT_MANAGER_H

#define ELEMENT_MANAGER_H

#include <QWidget>
#include <QObject>
#include <QList>
#include <QMap>

class ElementManager : public QObject {
    
    Q_OBJECT
    
    private:
        QList<QString>         m_Names;
        QMap<QString,QWidget*> m_Elements;
        
    public:
        const QList<QString>& names();
        bool push(const QString& name, QWidget* element);
        QWidget* get(const QString& name);
        void lock();
        void lock(const QString& name);
        void unlock();
        void unlock(const QString& name);
};

#endif
