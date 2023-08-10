#ifndef ADC_VIEWS_HEX_EDITOR_H

#define ADC_VIEWS_HEX_EDITOR_H

#define HEX_VIEWER_ROW_WIDTH 8

#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QFont>

class HexOffset : public QLabel {
    // Does nothing atm...
};

class HexValue : public QLabel {
    // Does nothing atm...
};

class HexViewer : public QWidget {
    
    private:
        
        QFont*              m_Font;
        QVector<HexOffset*> m_Offsets;
        QVector<HexValue*>  m_Values;
        quint64             m_Rows;
        quint64             m_Length;
        QVector<quint64>    m_Data;
        
        QWidget* make_Offsets(quint64 len);
        QWidget* make_Values(quint64 len);
        
    public:
        HexViewer(quint64 len = 128);
        ~HexViewer();
        bool set_Data(QByteArray& data, quint8 bytes);
        QVector<quint64>& get_Data();
        quint64 get_Rows();
        quint64 get_Length();
};

#endif
