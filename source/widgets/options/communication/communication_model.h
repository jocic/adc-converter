#ifndef ADC_WIDGETS_COMMUNICATION_MODEL_H

#define ADC_WIDGETS_COMMUNICATION_MODEL_H

#include "mvc/abstract_model.h"

class CommunicationModel : public AbstractModel {
    
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
        CommunicationModel::Mode get_Mode();
        void set_Mode(QString value);
        void set_Mode(CommunicationModel::Mode value);
};

#endif
