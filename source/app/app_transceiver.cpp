#include "app/app_transceiver.h"
#include "app/app_mediator.h"

bool AppTransceiver::tuneTo(QString channel) {
    
    AppMediator* app_mediator = AppMediator::get_Instance();
    
    app_mediator->add_Consumer((AbstractController*)this, channel);
    
    return true;
}
