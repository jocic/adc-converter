#include <QtMath>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "hex_viewer.h"

HexViewer::HexViewer(quint64 len) {
    
    // Core Parameters
    
    m_Rows   = qCeil(len / double(HEX_VIEWER_ROW_WIDTH));
    m_Length = len;
    
    quint64 filler_count = 0;
    
    if ((filler_count = (len % HEX_VIEWER_ROW_WIDTH)) != 0) {
        m_Length += HEX_VIEWER_ROW_WIDTH - filler_count;
    }
    
    // Arrange Offset & Hex Collumns
    
    QWidget*     wd_off  = new QWidget();
    QVBoxLayout* lay_off = new QVBoxLayout();
    QWidget*     wd_hex  = new QWidget();
    QVBoxLayout* lay_hex = new QVBoxLayout();
    
    wd_off->setStyleSheet("background: #e3e6e8");
    wd_off->setLayout(lay_off);
    lay_off->setContentsMargins(0, 0, 0, 0);
    lay_off->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
    
    wd_hex->setStyleSheet("background: #fff");
    wd_hex->setLayout(lay_hex);
    lay_hex->setContentsMargins(0, 0, 0, 0);
    lay_hex->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
    
    QWidget* wd_off_vals = this->make_Offsets(m_Rows);
    QWidget* wd_hex_vals = this->make_Values(m_Rows);
    
    lay_off->addWidget(wd_off_vals);
    lay_hex->addWidget(wd_hex_vals);
    
    // Arrange Layout
    
    QHBoxLayout* lay_main = new QHBoxLayout();
    
    lay_main->addWidget(wd_off);
    lay_main->addWidget(wd_hex);
    lay_main->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
    
    this->setLayout(lay_main);
}

HexViewer::~HexViewer() {
    
    for (quint64 i = 0; i < m_Offsets.size(); i++) {
        delete m_Offsets[i];
    }
    
    for (quint64 i = 0; i < m_Values.size(); i++) {
        delete m_Values[i];
    }
}

bool HexViewer::set_Data(QByteArray& data, quint8 bytes) {
    
    if (data.size() > 0) {
        
        quint64 i = 0;
        
        for (const auto& n : data) {
            
            QString hex_val = QString::asprintf("%02X", n & 0xFF);
            
            if (i < m_Values.size()) {
                m_Values.at(i++)->setText(hex_val);
            } else {
                break;
            }
        }
        
        while (i++ < m_Values.size()) {
            m_Values.at(i)->setText("..");
        }
        
        return true;
    }
    
    return false;
}

QVector<quint64>& HexViewer::get_Data() {
    return m_Data;
}

quint64 HexViewer::get_Length() {
    return m_Length;
}

QWidget* HexViewer::make_Offsets(quint64 len) {
    
    QWidget*     wd_off  = new QWidget();
    QVBoxLayout* lay_off = new QVBoxLayout();
    
    lay_off->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
    lay_off->setContentsMargins(6, 3, 6, 3);
    
    wd_off->setLayout(lay_off);
    
    for (quint64 i = 0; i < len; i++) {
        
        HexOffset* lbl_offset = new HexOffset();
        
        lbl_offset->setText(QString::asprintf("%08llu", i * HEX_VIEWER_ROW_WIDTH));
        lay_off->addWidget(lbl_offset);
        
        m_Offsets.push_back(lbl_offset);
    }
    
    return wd_off;
}

QWidget* HexViewer::make_Values(quint64 len) {
    
    QWidget*     wd_vals  = new QWidget();
    QVBoxLayout* lay_vals = new QVBoxLayout();
    
    lay_vals->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
    lay_vals->setContentsMargins(6, 3, 6, 3);
    
    wd_vals->setLayout(lay_vals);
    
    for (quint64 i = 0; i < len; i++) {
        
        QWidget*     wd_vals_in  = new QWidget();
        QHBoxLayout* lay_vals_in = new QHBoxLayout();
        
        lay_vals_in->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        lay_vals_in->setContentsMargins(0, 0, 0, 0);
        
        wd_vals_in->setLayout(lay_vals_in);
        
        for (quint64 j = 0; j < HEX_VIEWER_ROW_WIDTH; j++) {
            
            HexValue* lbl_value = new HexValue();
            
            lbl_value->setText(".");
            lbl_value->setMinimumWidth(15);
            lbl_value->setAlignment(Qt::AlignmentFlag::AlignHCenter);
            
            lay_vals_in->addWidget(lbl_value);
            
            m_Values.push_back(lbl_value);
        }
        
        lay_vals->addWidget(wd_vals_in);
    }
    
    return wd_vals;
}
