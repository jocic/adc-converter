#ifndef ADC_POPOVERS_PROCESSING_VIEW_H

#define ADC_POPOVERS_PROCESSING_VIEW_H

#include "app/mvc/abstract_view.h"

class ProcessingView : public AbstractView {
    
    protected:
        QString m_Notice;
    
    public:
        void initialize(QWidget* parent) override;
        QString get_Notice();
        void set_Notice(QString value);
};

#endif
