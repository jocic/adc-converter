#include <QDebug>
#include <QtAlgorithms>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>

#include "app/app_mediator.h"
#include "views/scope/scope_controller.h"
#include "views/scope/scope_view.h"

void ScopeController::on_View_Initialized(ElementManager* manager) {
    
    this->tuneTo(AppMediator::Channel::STREAM_EVENTS);
    this->tuneTo(AppMediator::Channel::STREAM_PARAMS);
    this->tuneTo(AppMediator::Channel::REFERENCE_PARAMS);
    this->tuneTo(AppMediator::Channel::SCOPE_DATA);
    
    m_BitsPerSample = 16;
    m_SamplesSigned = true;
}

void ScopeController::on_View_Changed() {
    
    // Does nothing...
}

void ScopeController::on_Model_Changed(QString key, QString value) {
    
    // Does nothing...
}

void ScopeController::on_Model_Cleared() {
    
    // Does nothing...
}
#include <QList>
#include <QPointF>
void ScopeController::on_Broadcast(quint64 ch, app_data_t data) {
    
    ScopeView*  view  = (ScopeView*)this->get_View();
    
    ElementManager* manager = view->get_ElementManager();
    
    QSplineSeries* chart_series = (QSplineSeries*)manager->get("ser");
    QValueAxis*    x_axis = (QValueAxis*)manager->get("x");
    QValueAxis*    y_axis = (QValueAxis*)manager->get("y");
    
    static quint64 x = 0;
    
    static QList<QPointF> test;
    
    ////////////////////////
    
    if (ch == AppMediator::Channel::REFERENCE_PARAMS) {
        
        m_ConversionTable.clear();
        
        //////////////////////////
        
        qint64 upper_limit = 0;
        qint64 lower_limit = 0;
        
        if (m_SamplesSigned) {
            upper_limit = pow(2, m_BitsPerSample - 1);
            lower_limit = upper_limit * -1;
        } else {
            upper_limit = pow(2, m_BitsPerSample);
            lower_limit = 0;
        }
        
        //////////////////////////
        
        quint64 adc_range = abs(data.ref_config.adc_negative)
            + abs(data.ref_config.adc_positive);
        
        quint64 adc_resolution = pow(2, m_BitsPerSample);
        
        qreal voltage_increment = qreal(adc_range) / adc_resolution;
        
        for (qint64 i = lower_limit, j = 0; i <= upper_limit; i++, j++) {
            m_ConversionTable[i] = data.ref_config.adc_negative
                + (j * voltage_increment);
        }
        
        //////////////////////////
        
        m_AdcNegative     = data.ref_config.adc_negative;
        m_AdcPositive     = data.ref_config.adc_positive;
        m_ApplyConversion = data.ref_config.convert_values;
        
        if (m_ApplyConversion) {
            y_axis->setRange(data.ref_config.adc_negative,
                data.ref_config.adc_positive);
        } else {
            y_axis->setRange(lower_limit, upper_limit);
        }
    }
    
    ////////////////////////
    
    else if (ch == AppMediator::Channel::STREAM_EVENTS) {
        
        if (data.event == "new_stream") {
            
            chart_series->clear();
            
            x_axis->setRange(0, 48);
            
            x = 0;
        }
        else if (data.event == "new_sample") {
            
            qint64 value = data.value.i64;
            
            if (m_ApplyConversion) {
                value = m_ConversionTable[value];
            }
            
            test.push_back(QPointF(x, value));
            
            x+=1;
            
            if (test.size() == 48) {
                x_axis->setRange(x - 48, x - 1);
                chart_series->replace(test);
                test.clear();
            }
        }
    }
    
    ////////////////////////
    
    else if (ch == AppMediator::Channel::SCOPE_DATA) {
        
        chart_series->clear();
        
        x_axis->setRange(data.scope_data.x_axis.first,
            data.scope_data.x_axis.second - 1);
        
         x = data.scope_data.x_axis.first;
        
        if (m_SamplesSigned) {
            
            for (const auto& sample : data.scope_data.samples) {
                
                qint64 value = 0;
                
                switch (m_BitsPerSample) {
                    case 8:
                        value = qint8(sample);
                        break;
                    case 16:
                        value = qint16(sample);
                        break;
                    case 32:
                        value = qint32(sample);
                        break;
                }
                
                if (m_ApplyConversion) {
                    value = m_ConversionTable[value];
                }
                
                chart_series->append(x++, value);
            }
        }
        else {
            
            for (const auto& sample : data.scope_data.samples) {
                
                quint64 value = 0;
                
                switch (m_BitsPerSample) {
                    case 8:
                        value = quint8(sample);
                        break;
                    case 16:
                        value = quint16(sample);
                        break;
                    case 32:
                        value = quint32(sample);
                        break;
                }
                
                if (m_ApplyConversion) {
                    value = m_ConversionTable[value];
                }
                
                chart_series->append(x++, value);
            }
        }
    }
    
    ////////////////////////
    
    else if (ch == AppMediator::Channel::STREAM_PARAMS) {
        
        quint8 bits_per_sample = data.stream_config.bits_per_sample;
        bool   samples_signed  = data.stream_config.signed_samples;
        
        m_BitsPerSample = bits_per_sample;        
        m_SamplesSigned = samples_signed;
        
        qint64 min_range = 0, max_range = 0;
        
        if (samples_signed) {
            max_range = pow(2, bits_per_sample - 1);
            min_range = max_range * -1;
        } else {
            max_range = pow(2, bits_per_sample);
            min_range = 0;
        }
        
        //////////////////////////
        
        qint64 upper_limit = 0;
        qint64 lower_limit = 0;
        
        if (m_SamplesSigned) {
            upper_limit = pow(2, m_BitsPerSample - 1);
            lower_limit = upper_limit * -1;
        } else {
            upper_limit = pow(2, m_BitsPerSample);
            lower_limit = 0;
        }
        
        if (m_ApplyConversion) {
            y_axis->setRange(m_AdcPositive, m_AdcNegative);
        } else {
            y_axis->setRange(lower_limit, upper_limit);
        }
    }
}
