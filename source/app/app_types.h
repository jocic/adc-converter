#include <QtGlobal>
#include <QVector>
#include <QMap>

typedef struct app_events {
    QString               event;
    QMap<QString,QString> params;
} app_events_t;

/////////////////////////////

typedef struct app_request {
    QString               request;
    QMap<QString,QString> params;
} app_request_t;

/////////////////////////////

typedef struct stream_event {
    QString               event;
    QMap<QString,QString> params;
} stream_event_t;

/////////////////////////////

typedef struct stream_params {
    quint64 sample_rate;
    quint8  bits_per_sample;
    bool    signed_samples;
} stream_params_t;

/////////////////////////////

typedef struct ref_params {
    qint64 positive;
    qint64 negative;
    bool   convert_values;
} ref_params_t;

/////////////////////////////

typedef struct com_params {
    qint64 positive;
    qint64 negative;
    bool   convert_values;
} com_params_t;

/////////////////////////////

typedef struct scope_data {
    QVector<qint64>       samples;
    QPair<qint64, qint64> x_axis;
    QPair<qint64, qint64> y_axis;
} scope_data_t;
