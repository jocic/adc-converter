#ifndef ADC_OPT_REF_MODEL_H

#define ADC_OPT_REF_MODEL_H

#include "mvc/abstract_model.h"

class RefModel : public AbstractModel {
    
    public:
    
        static const QString FIELD_POSITIVE;
        static const QString FIELD_NEGATIVE;
        
        quint16 get_Positive();
        void set_Positive(quint16 value);
        quint16 get_Negative();
        void set_Negative(quint16 value);
};

#endif
