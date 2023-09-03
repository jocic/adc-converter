#ifndef ADC_WIDGETS_COMMUNICATION_MODEL_H

#define ADC_WIDGETS_COMMUNICATION_MODEL_H

#include "app/mvc/abstract_model.h"

class CommunicationModel : public AbstractModel {
    
    public:
        
        enum Mode {
            ModeUnknown = -1,
            ModeText    =  0,
            ModeBinary  =  1
        };
        
        Q_ENUM(Mode);
        
        enum Endianness {
            EndiannessUnknown = -1,
            EndiannessBig     =  0,
            EndiannessSmall   =  1
        };
        
        Q_ENUM(Endianness);
        
        static const QString FIELD_PORT;
        static const QString FIELD_MODE;
        static const QString FIELD_ENDIANNESS;
        
        QString get_Port();
        void setPort(QString value);
        CommunicationModel::Mode get_Mode();
        void set_Mode(QString value);
        void set_Mode(CommunicationModel::Mode value);
        CommunicationModel::Endianness get_Endianness();
        void set_Endianness(QString value);
        void set_Endianness(CommunicationModel::Endianness value);
};

#endif
