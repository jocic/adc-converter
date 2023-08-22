#ifndef ADC_WIDGETS_CONTROLS_MODEL_H

#define ADC_WIDGETS_CONTROLS_MODEL_H

#include "app/mvc/abstract_model.h"

class ControlsModel : public AbstractModel {
    
    public:
        
        static const QString FIELD_CONNECT;
        static const QString FIELD_REFRESH;
        static const QString FIELD_SIMULATE;
};

#endif
