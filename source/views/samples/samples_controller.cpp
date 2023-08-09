#include <QtMath>
#include <QDebug>
#include <QMap>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

#include "samples_model.h"
#include "samples_view.h"
#include "samples_controller.h"
#include "file_loader.h"

void SamplesController::on_View_Initialized(ElementManager* manager) {
    
    // Register Fields
    
    this->registerField(SamplesModel::FIELD_OFFSET_START,
        QLineEdit::staticMetaObject.className());
    
    this->registerField(SamplesModel::FIELD_RANGE_SPAN,
        QComboBox::staticMetaObject.className());
    
    // Connect Actuators
    
    QPushButton* btn_offset = (QPushButton*)manager
        ->get(SamplesModel::FIELD_OFFSET);
    
    QPushButton* btn_prev = (QPushButton*)manager
        ->get(SamplesModel::FIELD_PREV);
    
    QPushButton* btn_next = (QPushButton*)manager
        ->get(SamplesModel::FIELD_NEXT);
    
    connect(btn_offset, &QPushButton::clicked,
        this, &SamplesController::on_Clicked_Offset);
    
    connect(btn_prev, &QPushButton::clicked,
        this, &SamplesController::on_Clicked_Prev);
    
    connect(btn_next, &QPushButton::clicked,
        this, &SamplesController::on_Clicked_Next);
}

void SamplesController::on_View_Changed() {
    
    // Does nothing...
}

void SamplesController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == SamplesModel::FIELD_OFFSET_START) {
        
        QLineEdit* txt_offset = (QLineEdit*)manager
            ->get(SamplesModel::FIELD_OFFSET_START);
        
        txt_offset->setText(value);
    }
    else if (key == SamplesModel::FIELD_RANGE_SPAN) {
        
        QComboBox* cb_span = (QComboBox*)manager
            ->get(SamplesModel::FIELD_RANGE_SPAN);
        
        quint64 range = value.toUInt();
        
        cb_span->clear();
        
        for (quint8 i = 0; i < 3 & range <= 1280; i++) {
            cb_span->addItem(QString::asprintf("%llu", range));
            range *= 2;
        }
    }

}

void SamplesController::on_Model_Cleared() {
    
    // Does nothing...
}

void SamplesController::on_Mediator_Notify(QString topic,
    QMap<QString,QString> params) {
    
    qDebug() << "Meidator notification:" << topic << params;
    
    if (topic == "wd_stream_data") {
        
        SamplesModel* model = (SamplesModel*)this->get_Model();
        
        quint64 sample_rate = 0;
        
        if (params.contains("txt_SampleRate")) {
            sample_rate = params["txt_SampleRate"].toUInt();
        }
        
        quint64 range = qMin(1280, qMax(16, qCeil(sample_rate / 8000)));
        
        if ((range % 16) != 0) {
            range += (16 - (range % 16));
        }
        
        model->set_OffsetStart(0);
        model->set_RangeSpan(range);
    }
    
}

void SamplesController::on_Clicked_Offset() {
    
    SamplesView* view = (SamplesView*)this->get_View();
    
    QVector<QLabel*>* test = view->test();
    
    FileLoader* loader = FileLoader::get_Instance();
    
    for (int i = 0; i < loader->get_Buffer()->size() && i < 1280; i++) {
        
        quint8 word = loader->get_Buffer()->at(i);
        
        test->at(i)->setVisible(true);
        test->at(i)->setText(QString::asprintf("%02X", word));
    }
}

void SamplesController::on_Clicked_Prev() {
    qDebug() << "prev clicked";
}

void SamplesController::on_Clicked_Next() {
    qDebug() << "next clicked";
}
