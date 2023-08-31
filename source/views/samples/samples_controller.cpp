#include <QtMath>
#include <QDebug>
#include <QMap>
#include <QVector>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

#include "samples_model.h"
#include "samples_view.h"
#include "samples_controller.h"
#include "app/app_core.h"
#include "app/app_loader.h"
#include "app/app_mediator.h"
#include "app/workers/load_worker.h"

void SamplesController::on_View_Initialized(ElementManager* manager) {
    
    this->tuneTo(AppMediator::Channel::APP_EVENTS);
    this->tuneTo(AppMediator::Channel::STREAM_EVENTS);
    this->tuneTo(AppMediator::Channel::STREAM_PARAMS);
    
    //////////////////////////////
    
    // Init Model
    
    SamplesModel* model = (SamplesModel*)this->get_Model();
    
    model->set_OffsetStart(0);
    model->set_RangeSpan(48);
    model->set_BitsPerSample(16);
    
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
    
    // Connect Loader
    
    AppLoader* loader = AppLoader::get_Instance();
    LoadWorker* worker = (LoadWorker*)loader->get_Worker();
    
    connect(worker, &LoadWorker::sig_Done,
        this, &SamplesController::on_Data_Loaded);
}

void SamplesController::on_View_Changed() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    SamplesView* view  = (SamplesView*)this->get_View();
    
    // Offset Start
    
    QLineEdit* txt_offset_start = (QLineEdit*)manager
        ->get(SamplesModel::FIELD_OFFSET_START);
    
    QString offset_start = txt_offset_start->text();
    
    this->get_Model()->set(SamplesModel::FIELD_OFFSET_START, offset_start, true);
    
    // Range Span
    
    QComboBox* comb_range_span = (QComboBox*)manager
        ->get(SamplesModel::FIELD_RANGE_SPAN);
    
    QString range_span = comb_range_span->currentText();
    
    this->get_Model()->set(SamplesModel::FIELD_RANGE_SPAN, range_span, true);
    
    HexViewer* hex_viewer = view->get_HexViewer();
    
    hex_viewer->set_VisibleRows(range_span.toUInt() / 8);
    
    // Samples
    
    QLabel* lbl_samples = (QLabel*)manager->get(SamplesModel::VALUE_SAMPLES);
    
    quint64 range_span_val = range_span.toUInt();
    quint64 off_start_val  = offset_start.toUInt();
    quint64 off_end_val    = off_start_val + range_span_val;
    
    QString offset_end = QString::asprintf("%llu", off_start_val + off_end_val);
    
    lbl_samples->setText(offset_start + " - " + offset_end);
    
    // Time
    
    QLabel* lbl_time = (QLabel*)manager->get(SamplesModel::VALUE_TIME);
    
    quint8 range_ind = comb_range_span->currentIndex();
    
    quint64 time_start_val = (off_start_val / (range_span_val / (range_ind + 1))) * 5;
    quint64 time_end_val   = time_start_val + 5 + range_ind * 5;
    
    lbl_time->setText(QString::asprintf("%llu", time_start_val) +
        " - " + QString::asprintf("%llu", time_end_val));
    
    // Temp
    
    app_data_t data;
    
    QVector<quint64>& samples = hex_viewer->get_Data();
    
    for (const auto& sample : samples) {
        data.scope_data.samples.push_back(sample & 0xFFFF);
    }
    
    data.scope_data.x_axis.first  = off_start_val;
    data.scope_data.x_axis.second = off_end_val;
    
    emit SamplesController::sig_Broadcast(
        AppMediator::Channel::SCOPE_DATA, data);
}

void SamplesController::on_Model_Changed(QString key, QString value) {
    
    SamplesModel* model = (SamplesModel*)this->get_Model();
    SamplesView*  view  = (SamplesView*)this->get_View();
    
    ElementManager* manager = view->get_ElementManager();
    
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
        
        for (quint8 i = 0; i < cb_span->count(); i++) {
            
            if (cb_span->itemText(i) == value) {
                cb_span->setCurrentIndex(i); break;
            }
        }
    }
}

void SamplesController::on_Model_Cleared() {
    
    // Does nothing...
}

void SamplesController::on_Broadcast(quint64 ch, app_data_t data) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    QPushButton* btn_offset = (QPushButton*)manager
        ->get(SamplesModel::FIELD_OFFSET);
    
    QPushButton* btn_prev = (QPushButton*)manager
        ->get(SamplesModel::FIELD_PREV);
    
    QPushButton* btn_next = (QPushButton*)manager
        ->get(SamplesModel::FIELD_NEXT);
    
    QLineEdit* txt_offset = (QLineEdit*)manager
        ->get(SamplesModel::FIELD_OFFSET_START);
    
    QComboBox* cb_span = (QComboBox*)manager
        ->get(SamplesModel::FIELD_RANGE_SPAN);
    
    //////////////////////////////
    
    if (ch == AppMediator::Channel::APP_EVENTS) {
        
        if (data.event == "dump_loaded") {
            this->on_Clicked_Offset();
        }
    }
    
    //////////////////////////////
    
    else if (ch == AppMediator::Channel::STREAM_EVENTS) {
        
        if (data.event == "new_stream") {
            
            SamplesView*  view  = (SamplesView*)this->get_View();
            
            HexViewer* hex_viewer = view->get_HexViewer();
            
            hex_viewer->get_Data().clear();
            
            this->on_Data_Loaded(); // Reset Hex Viewer
            
            this->on_View_Changed();
        }
        else if (data.event == "stream_started") {
            
            btn_offset->setEnabled(false);
            btn_prev->setEnabled(false);
            btn_next->setEnabled(false);
            txt_offset->setEnabled(false);
            cb_span->setEnabled(false);
        }
        else if (data.event == "stream_ended") {
            
            btn_offset->setEnabled(true);
            btn_prev->setEnabled(true);
            btn_next->setEnabled(true);
            txt_offset->setEnabled(true);
            cb_span->setEnabled(true);
            
            this->on_Data_Loaded();
        }
    }
    
    //////////////////////////////
    
    else if (ch == AppMediator::Channel::STREAM_PARAMS) {
        
        SamplesModel* model = (SamplesModel*)this->get_Model();
        SamplesView*  view  = (SamplesView*)this->get_View();
        
        ElementManager* manager = view->get_ElementManager();
        
        HexViewer* hex_viewer = view->get_HexViewer();
        
        quint64 sample_rate     = data.stream_config.sample_rate;
        quint8  bits_per_sample = data.stream_config.bits_per_sample;
        
        quint64 range = qMax(1, qCeil(sample_rate / double(1000)));
        
        if ((range % 8) != 0) {
            range += (8 - (range % 8));
        }
        
        QComboBox* cb_span = (QComboBox*)manager
            ->get(SamplesModel::FIELD_RANGE_SPAN);
        
        for (quint64 i = 0, j = range; i < 3; i++, j += range) {
            cb_span->setItemText(i, QString::asprintf("%llu", j));
        }
        
        hex_viewer->set_VisibleRows(range / 8);
        
        model->set_OffsetStart(0);
        model->set_RangeSpan(range);
        model->set_BitsPerSample(bits_per_sample);
        
        this->on_Data_Loaded(); // Reset Hex Viewer
        
        this->on_View_Changed();
    }
}

void SamplesController::on_Data_Loaded() {
    
    SamplesModel* model = (SamplesModel*)this->get_Model();
    SamplesView*  view  = (SamplesView*)this->get_View();
    
    AppCore*    app_core   = AppCore::get_Instance();
    HexViewer*  hex_viewer = view->get_HexViewer();
    
    quint64 rs    = model->get_RangeSpan();
    quint8  bps   = model->get_BitsPerSample();
    quint8  bytes = bps / 8;
    
    QByteArray buffer;
    app_core->get_Chunk(buffer, 0, rs * bytes);
    
    hex_viewer->set_Offset(0);
    hex_viewer->set_VisibleRows(rs / 8);
    hex_viewer->set_Data(buffer, bytes);
}

void SamplesController::on_Clicked_Offset() {
    
    SamplesModel* model = (SamplesModel*)this->get_Model();
    SamplesView*  view  = (SamplesView*)this->get_View();
    
    AppCore*    app_core   = AppCore::get_Instance();
    HexViewer*  hex_viewer = view->get_HexViewer();
    
    quint64 offset = model->get_OffsetStart();
    quint64 rs     = model->get_RangeSpan();
    quint8  bps    = model->get_BitsPerSample();
    quint8  bytes  = bps / 8;
    
    QByteArray buffer;
    
    app_core->get_Chunk(buffer, offset * bytes, rs * bytes);
    
    hex_viewer->set_Offset(offset);
    hex_viewer->set_VisibleRows(rs / 8);
    hex_viewer->set_Data(buffer, bytes);
    
    this->on_View_Changed();
}

void SamplesController::on_Clicked_Prev() {
    
    SamplesModel* model = (SamplesModel*)this->get_Model();
    SamplesView*  view  = (SamplesView*)this->get_View();
    
    AppCore*    app_core   = AppCore::get_Instance();
    HexViewer*  hex_viewer = view->get_HexViewer();
    
    quint64 offset = model->get_OffsetStart();
    quint64 rs     = model->get_RangeSpan();
    quint8  bps    = model->get_BitsPerSample();
    quint8  bytes  = bps / 8;
    
    if (offset % rs != 0) {
        offset += (rs - offset % rs);
    }
    
    if (offset < rs) {
        offset = 0;
    } else {
        offset -= rs;
    }
    
    qDebug() << "Prev:" << offset;
    
    model->set_OffsetStart(offset);
    
    QByteArray buffer;
    
    app_core->get_Chunk(buffer, offset * bytes, rs * bytes);
    
    hex_viewer->set_Offset(offset);
    hex_viewer->set_VisibleRows(rs / 8);
    hex_viewer->set_Data(buffer, bytes);
    
    this->on_View_Changed();
}

void SamplesController::on_Clicked_Next() {
    
    SamplesModel* model = (SamplesModel*)this->get_Model();
    SamplesView*  view  = (SamplesView*)this->get_View();
    
    AppCore*    app_core   = AppCore::get_Instance();
    HexViewer*  hex_viewer = view->get_HexViewer();
    
    quint64 offset = model->get_OffsetStart();
    quint64 rs     = model->get_RangeSpan();
    quint8  bps    = model->get_BitsPerSample();
    quint8  bytes  = bps / 8;
    
    if (offset % rs != 0) {
        offset += (rs - offset % rs);
    }
    
    offset += rs;
    
    qDebug() << "Next:" << offset;
    
    model->set_OffsetStart(offset);
    
    QByteArray buffer;
    
    app_core->get_Chunk(buffer, offset * bytes, rs * bytes);
    
    hex_viewer->set_Offset(offset);
    hex_viewer->set_VisibleRows(rs / 8);
    hex_viewer->set_Data(buffer, bytes);
    
    this->on_View_Changed();
}
