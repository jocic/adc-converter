#ifndef ADC_CORE_ABSTRACT_MODEL

#define ADC_CORE_ABSTRACT_MODEL

#include <QObject>
#include <QMap>

//#include "model_attribute.h"

class AbstractModel : public QObject {
    
    Q_OBJECT
    
    private:
        //QMap<QString,ModelAttribute> m_Attributes;
    
    public:
         //virtual void clear();
};

#endif
