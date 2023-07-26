#ifndef ADC_OPTIONS_BPS_WIDGET

#define ADC_OPTIONS_BPS_WIDGET

#include "abstract_widget.h"
#include "bps_model.h"
#include "bps_view.h"
#include "bps_controller.h"

class BpsWidget : public AbstractWidget {
    
private:
    QWidget*       m_Parent;
    BpsModel*      m_Model;
    BpsView*       m_View;
    BpsController* m_Controller;
    
public:
    BpsWidget(QWidget* parent = NULL);
    const BpsModel* model();
    const BpsView* view();
    const BpsController* controller();
    
protected:
    void initialize() override;
};

#endif
