#ifndef ADC_CORE_APP_ICONS

#define ADC_CORE_APP_ICONS

#include <QObject>
#include <QIcon>

class AppIcons : public QObject {
    
    Q_OBJECT
    
    public:
        static const QIcon* PLAY;
        static const QIcon* STOP;
        static const QIcon* EXPORT;
};

#endif
