#include <QWidget>
#include <QProgressBar>

#include "processing_popover.h"
#include "processing_model.h"
#include "processing_view.h"
#include "processing_controller.h"

ProcessingPopover::ProcessingPopover(QWidget* parent) : AbstractPopover(parent)  {
    
    // Nothing here, yet...
}

void ProcessingPopover::initialize() {
    
    m_Model      = new ProcessingModel();
    m_View       = new ProcessingView();
    m_Controller = new ProcessingController();
    
    m_Controller->set_Model(m_Model);
    m_Controller->set_View(m_View);
    
    connect(m_Model, &ProcessingModel::sig_Model_Updated,
        (ProcessingController*)m_Controller, &ProcessingController::on_Model_Changed);
    
    connect(m_Model, &ProcessingModel::sig_Model_Cleared,
        (ProcessingController*)m_Controller, &ProcessingController::on_Model_Cleared);
    
    connect(m_View, &ProcessingView::sig_View_Initialized,
        (ProcessingController*)m_Controller, &ProcessingController::on_View_Initialized);
    
    connect(m_View, &ProcessingView::sig_View_Changed,
        (ProcessingController*)m_Controller, &ProcessingController::on_View_Changed);
    
    ((ProcessingView*)m_View)->set_Notice("A process is being taken care, please wait...");
    
    m_View->initialize(this);
}
