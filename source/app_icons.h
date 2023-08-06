#ifndef ADC_COR_APP_ICONS_H

#define ADC_COR_APP_ICONS_H

#include <QObject>
#include <QIcon>

class AppIcons : public QObject {
    
    Q_OBJECT
    
    public:
        static const QIcon* MAIN;
        static const QIcon* PLAY;
        static const QIcon* STOP;
        static const QIcon* EXPORT;
};

#endif
