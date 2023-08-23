#include <QMap>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>

#include "stream_model.h"
#include "stream_controller.h"

void StreamController::on_View_Initialized(ElementManager* manager) {
    
    this->registerField(StreamModel::FIELD_SAMPLE_RATE,
        QLineEdit::staticMetaObject.className());
    
    this->registerField(StreamModel::FIELD_BITS_PER_SAMPLE,
        QComboBox::staticMetaObject.className());
    
    this->registerField(StreamModel::FIELD_SIGNED,
        QCheckBox::staticMetaObject.className());
}

void StreamController::on_View_Changed() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    StreamModel*    model   = (StreamModel*)this->get_Model();
    
    
    // Sample Rate
    
    QLineEdit* txt_sample = (QLineEdit*)manager
        ->get(StreamModel::FIELD_SAMPLE_RATE);
    
    quint64 sample_rate = txt_sample->text().toUInt();
    
    if (sample_rate < 0) {
        sample_rate = 0;
    } else if (sample_rate > 250000) {
        sample_rate = 250000;
    }
    
    model->set_SampleRate(sample_rate);
    
    // Bits per Sample
    
    QComboBox* combo_bits = (QComboBox*)manager
        ->get(StreamModel::FIELD_BITS_PER_SAMPLE);
    
    quint8 bits_per_sample = combo_bits->currentText().toUInt();
    
    model->set_BitsPerSample(bits_per_sample);
    
    // Sample Signed
    
    QCheckBox* cb_signed = (QCheckBox*)manager
        ->get(StreamModel::FIELD_SIGNED);
    
    model->set_Signed(cb_signed->isChecked());
    
    // Combile & Broadcast Data
    
    QMap<QString,QString> data;
    
    data.insert(StreamModel::FIELD_SAMPLE_RATE,
        QString::asprintf("%llu", sample_rate));
    data.insert(StreamModel::FIELD_BITS_PER_SAMPLE,
        QString::asprintf("%u", bits_per_sample));
    data.insert(StreamModel::FIELD_SIGNED,
        cb_signed->isChecked() ? "true" : "false");
    
    emit StreamController::sig_Mediator_Notify("wd_stream_data", data);
}

void StreamController::on_Model_Changed(QString key, QString value) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    if (key == StreamModel::FIELD_SAMPLE_RATE) {
        
        QLineEdit* sample_rate = (QLineEdit*)manager
            ->get(StreamModel::FIELD_SAMPLE_RATE);
        
        sample_rate->setText(value);
    }
    else if (key == StreamModel::FIELD_BITS_PER_SAMPLE) {
        
        QComboBox* bits_per_sample = (QComboBox*)manager
            ->get(StreamModel::FIELD_BITS_PER_SAMPLE);
        
        for (quint8 i = 0; i < bits_per_sample->count(); i++) {
            
            if (bits_per_sample->itemText(i) == value) {
                bits_per_sample->setCurrentIndex(i); break;
            }
        }
    }
    else if (key == StreamModel::FIELD_SIGNED) {
        
        QCheckBox* sample_signed = (QCheckBox*)manager
            ->get(StreamModel::FIELD_SIGNED);
        
        sample_signed->setChecked(value == "true");
    }
}

void StreamController::on_Model_Cleared() {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    if (manager == NULL) {
        return;
    }
    
    QLineEdit* sample_rate = (QLineEdit*)manager
        ->get(StreamModel::FIELD_SAMPLE_RATE);
    
    QComboBox* bits_per_sample = (QComboBox*)manager
        ->get(StreamModel::FIELD_BITS_PER_SAMPLE);
    
    QCheckBox* sample_signed = (QCheckBox*)manager
        ->get(StreamModel::FIELD_SIGNED);
    
    sample_rate->setText("44100");
    
    bits_per_sample->setCurrentIndex(0);
    
    sample_signed->setChecked(false);
}

void StreamController::on_Mediator_Notify(QString topic,
    QMap<QString,QString> params) {
    
    ElementManager* manager = this->get_View()->get_ElementManager();
    
    StreamModel* model = (StreamModel*)this->get_Model();
    
    QLineEdit* sample_rate = (QLineEdit*)manager
        ->get(StreamModel::FIELD_SAMPLE_RATE);
    
    QComboBox* bits_per_sample = (QComboBox*)manager
        ->get(StreamModel::FIELD_BITS_PER_SAMPLE);
    
    QCheckBox* sample_signed = (QCheckBox*)manager
        ->get(StreamModel::FIELD_SIGNED);
    
    if (topic == "stream_started") {
        sample_rate->setEnabled(false);
        bits_per_sample->setEnabled(false);
        sample_signed->setEnabled(false);
    }
    else if (topic == "stream_ended") {
        sample_rate->setEnabled(true);
        bits_per_sample->setEnabled(true);
        sample_signed->setEnabled(true);
    }
    else if (topic == "stream_params") {
        
        if (params.contains("sample_rate")) {
            model->set_SampleRate(params["sample_rate"]);
        }
        
        if (params.contains("bits_per_sample")) {
            model->set_BitsPerSample(params["bits_per_sample"]);
        }
        
        if (params.contains("signed_samples")) {
            model->set_Signed(params["signed_samples"]);
        }
    }
}
