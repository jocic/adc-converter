#ifndef ADC_CORE_MODEL_ATTRIBUTE

#define ADC_CORE_MODEL_ATTRIBUTE

#include <QObject>

class ModelAttribute : public QObject {
    
    Q_OBJECT
    
    private:
        QString value;
    
    public:
        const QString* get_Value();
    
};

#endif
