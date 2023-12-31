#ifndef ADC_POPOVERS_PROCESSING_MODEL_H

#define ADC_POPOVERS_PROCESSING_MODEL_H

#include "app/mvc/abstract_model.h"

class ProcessingModel : public AbstractModel {
    
    public:
    
    static const QString FIELD_PROGRESS;
    static const QString FIELD_CANCEL;
        
        QString get_Progress();
        void set_Progress(QString value);
        void set_Progress(quint8 value);
};

#endif
