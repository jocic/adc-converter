#include <QDebug>

#include "app/app_transceiver.h"
#include "app/app_mediator.h"

bool AppTransceiver::tuneTo(QString channel) {
    
    AppMediator* app_mediator = AppMediator::get_Instance();
    
    app_mediator->reg_Receiver(this, channel);
    
    return true;
}
