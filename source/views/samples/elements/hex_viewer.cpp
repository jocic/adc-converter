#include <QtMath>
#include <QMap>
#include <QSpacerItem>
#include <QFontDatabase>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "hex_viewer.h"
#include "app/app_mediator.h"

HexValue::HexValue() {
    this->setMouseTracking(true);
}


void HexValue::mousePressEvent(QMouseEvent *ev) {
    
    QMap<QString,QString> data;
    
    data.insert("val", this->text());
    
    AppMediator* mediator = AppMediator::get_Instance();
    
    emit mediator->sig_Notify("hex_selected", data);
}

HexViewer::HexViewer(quint64 len) {
    
    // Core Parameters
    
    m_Rows        = qCeil(len / double(HEX_VIEWER_ROW_WIDTH));
    m_RowsVisible = 6;
    m_Length      = len;
    m_Offset      = 0;
    
    quint64 filler_count = 0;
    
    if ((filler_count = (len % HEX_VIEWER_ROW_WIDTH)) != 0) {
        m_Length += HEX_VIEWER_ROW_WIDTH - filler_count;
    }
    
    // Font
    
    QFont sys_font = QFontDatabase::systemFont(QFontDatabase::SystemFont::FixedFont);
    
    m_Font = new QFont();
    
    m_Font->setFamily(sys_font.family());
    
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

void HexViewer::set_Offset(quint64 offset) {
    
    if (offset >= 0) {
        
        m_Offset = offset;
        
        for (const auto lbl_off : m_Offsets) {
            lbl_off->setText(QString::asprintf("%08llu", offset));
            offset += 8;
        }
    }
}

quint64 HexViewer::get_Offset() {
    return m_Offset;
}

void HexViewer::set_Data(QByteArray& data, quint8 bytes) {
    
    quint64 i = 0, j = 0;
    
    QString val_none = "..";
    
    if (bytes == 4) {
        val_none = "........";
    } else if (bytes == 3) {
        val_none = "......";
    } else if (bytes == 2) {
        val_none = "....";
    }
    
    m_Data.clear();
    
    while (i < m_Values.size()) {
        
        QString hex_val = val_none;
        quint64 raw_val = 0;
        
        if (j + (bytes - 1) < data.size()) {
            
            if (bytes == 4) {
                
                raw_val |= ((data[j++] & 0xFF)      );
                raw_val |= ((data[j++] & 0xFF) <<  8);
                raw_val |= ((data[j++] & 0xFF) << 16);
                raw_val |= ((data[j++] & 0xFF) << 24);
                
                hex_val = QString::asprintf("%08llX", raw_val & 0xFFFFFFFF);
            }
            else if (bytes == 3) {
                
                raw_val |= ((data[j++] & 0xFF)      );
                raw_val |= ((data[j++] & 0xFF) <<  8);
                raw_val |= ((data[j++] & 0xFF) << 16);
                
                hex_val = QString::asprintf("%06llX", raw_val & 0xFFFFFF);
            }
            else if (bytes == 2) {
                
                raw_val |= ((data[j++] & 0xFF)      );
                raw_val |= ((data[j++] & 0xFF) <<  8);
                
                hex_val = QString::asprintf("%04llX", raw_val & 0xFFFF);
            }
            else {
                
                raw_val |= ((data[j++] & 0xFF)      );
                
                hex_val = QString::asprintf("%02llX", raw_val & 0xFF);
            }
            
            m_Data.push_back(raw_val);
        }
        
        m_Values.at(i)->setText(hex_val);
        
        i++;
    }
}

QVector<quint64>& HexViewer::get_Data() {
    return m_Data;
}

quint64 HexViewer::get_Length() {
    return m_Length;
}

void HexViewer::set_VisibleRows(quint64 value) {
    
    if (value > 0 && value <= m_Rows) {
        
        for (quint64 i = 0; i < m_Rows; i++) {
            
            if (i < value) {
                m_Offsets[i]->setVisible(true);
                m_Wrappers[i]->setVisible(true);
            } else {
                m_Offsets[i]->setVisible(false);
                m_Wrappers[i]->setVisible(false);
            }
        }
        
        m_RowsVisible = value;
    }
}

quint64 HexViewer::get_VisibleRows() {
    return m_RowsVisible;
}

QWidget* HexViewer::make_Offsets(quint64 len) {
    
    QWidget*     wd_off  = new QWidget();
    QVBoxLayout* lay_off = new QVBoxLayout();
    
    lay_off->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
    lay_off->setContentsMargins(8, 4, 8, 4);
    
    wd_off->setLayout(lay_off);
    
    for (quint64 i = 0; i < len; i++) {
        
        HexOffset* lbl_offset = new HexOffset();
        
        lbl_offset->setText(QString::asprintf("%08llu", i * HEX_VIEWER_ROW_WIDTH));
        lbl_offset->setFont(*m_Font);
        
        if (i >= m_RowsVisible) {
            lbl_offset->setVisible(false);
        }
        
        lay_off->addWidget(lbl_offset);
        
        m_Offsets.push_back(lbl_offset);
    }
    
    return wd_off;
}

QWidget* HexViewer::make_Values(quint64 len) {
    
    QWidget*     wd_vals  = new QWidget();
    QVBoxLayout* lay_vals = new QVBoxLayout();
    
    lay_vals->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
    lay_vals->setContentsMargins(8, 4, 8, 4);
    
    wd_vals->setStyleSheet("QLabel:hover { background: #eee; }");
    wd_vals->setLayout(lay_vals);
    
    for (quint64 i = 0; i < len; i++) {
        
        QWidget*     wd_vals_in  = new QWidget();
        QHBoxLayout* lay_vals_in = new QHBoxLayout();
        
        lay_vals_in->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        lay_vals_in->setContentsMargins(0, 0, 0, 0);
        
        wd_vals_in->setLayout(lay_vals_in);
        
        if (i >= m_RowsVisible) {
            wd_vals_in->setVisible(false);
        }
        
        for (quint64 j = 0; j < HEX_VIEWER_ROW_WIDTH; j++) {
            
            HexValue* lbl_value = new HexValue();
            
            lbl_value->setText("..");
            lbl_value->setFont(*m_Font);
            lbl_value->setAlignment(Qt::AlignmentFlag::AlignHCenter);
            
            lay_vals_in->addWidget(lbl_value);
            
            m_Values.push_back(lbl_value);
        }
        
        lay_vals->addWidget(wd_vals_in);
        
        m_Wrappers.push_back(wd_vals_in);
    }
    
    return wd_vals;
}
