#include <QDebug>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>

#include "mvc/element_manager.h"
#include "general_model.h"
#include "general_view.h"

void GeneralView::initialize(QWidget* parent) {
    
    // Arrange View
    
    QGroupBox*   box              = new QGroupBox();
    QFormLayout* lay_root         = new QFormLayout();
    QLabel*      lbl_samples      = new QLabel();
    QLabel*      lbl_samples_val  = new QLabel();
    QLabel*      lbl_duration     = new QLabel();
    QLabel*      lbl_duration_val = new QLabel();
    
    box->setLayout(lay_root);
    box->setTitle("General");
    
    lbl_samples->setText("Samples:");
    lbl_samples_val->setText("N/D");
    lay_root->addRow(lbl_samples, lbl_samples_val);
    
    lbl_duration->setText("Duration:");
    lbl_duration_val->setText("N/D");
    lay_root->addRow(lbl_duration, lbl_duration_val);
    
    parent->layout()->addWidget(box);
    
    // Push References
    
    ElementManager* manager = this->get_ElementManager();
    
    manager->push(GeneralModel::FIELD_SAMPLES, lbl_samples_val);
    manager->push(GeneralModel::FIELD_DURATION, lbl_duration_val);
    
    emit GeneralView::sig_View_Initialized(manager);
}
