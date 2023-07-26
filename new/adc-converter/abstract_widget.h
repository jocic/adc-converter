#ifndef ADC_CORE_ABSTRACT_WIDGET

#define ADC_CORE_ABSTRACT_WIDGET

#include <QWidget>
#include <QIODevice>

class AbstractWidget : public QWidget {
    
protected:
    virtual void initialize() = 0;
};

#endif
