#ifndef ELEMENT_MANAGER_H

#define ELEMENT_MANAGER_H

#include <QObject>
#include <QList>
#include <QMap>

class ElementManager {
    
    QList<QString> m_Names;
    
public:
    ElementManager();
    const QList<QString>& names();
    bool push(QString name, QObject* element);
    QObject* get(QString name);
    void lock();
    void lock(QString name);
    void unlock();
    void unlock(QString name);
};

#endif
