#include <QDebug>

#include "app/app_transceiver.h"
#include "app/app_mediator.h"

bool AppTransceiver::tuneTo(quint64 ch) {
    
    AppMediator* app_mediator = AppMediator::get_Instance();
    
    app_mediator->reg_Receiver(this, ch);
    
    return true;
}
