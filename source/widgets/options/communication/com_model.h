#ifndef ADC_OPT_COM_MODEL_H

#define ADC_OPT_COM_MODEL_H

#include "mvc/abstract_model.h"

class ComModel : public AbstractModel {
    
    public:
        
        enum Mode {
            Unknown = -1,
            Text    =  0,
            Binary  =  1
        };
        
        Q_ENUM(Mode);
        
        static const QString FIELD_PORT;
        static const QString FIELD_MODE;
        
        QString get_Port();
        void setPort(QString value);
        ComModel::Mode get_Mode();
        void set_Mode(QString value);
        void set_Mode(ComModel::Mode value);
};

#endif
