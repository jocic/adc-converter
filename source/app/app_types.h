#ifndef ADC_APP_APP_TYPES_H

#define ADC_APP_APP_TYPES_H

#include <QtGlobal>
#include <QVector>
#include <QMap>

union gen_value {
    qint64  i64;
    quint64 ui64;
};

/////////////////////////////

typedef struct stream_config {
    quint64 sample_rate;
    quint8  bits_per_sample;
    bool    signed_samples;
} stream_config_t;

/////////////////////////////

typedef struct reference_config {
    qint64  adc_positive;
    qint64  adc_negative;
    bool    convert_values;
} reference_config_t;

/////////////////////////////

typedef struct communication_config {
    QString com_port;
    QString com_mode;
} communication_config_t;

/////////////////////////////

typedef struct scope_data {
    QVector<qint64>       samples;
    QPair<qint64, qint64> x_axis;
} scope_data_t;

/////////////////////////////

typedef struct app_data {
    QString                event;
    QString                str_value;
    gen_value              value;
    QMap<QString,QString>  params;
    stream_config_t        stream_config;
    reference_config_t     ref_config;
    communication_config_t com_config;
    scope_data_t           scope_data;
} app_data_t;

#endif
