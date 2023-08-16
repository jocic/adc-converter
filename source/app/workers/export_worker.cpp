#include <QDebug>
#include <QtGlobal>

#include "export_worker.h"

ExportWorker::ExportWorker() {
    
    m_SampleRate    = 44100;
    m_BitsPerSample = 16;
    m_SignedSamples = false;
}

quint32 ExportWorker::get_SampleRate() {
    return m_SampleRate;
}

void ExportWorker::set_SampleRate(quint32 sample_rate) {
    m_SampleRate = sample_rate;
}

quint8 ExportWorker::get_BitsPerSample() {
    return m_BitsPerSample;
}

void ExportWorker::set_BitsPerSamplee(quint8 bits_per_sample) {
    
    if (bits_per_sample % 8 == 0) {
        m_BitsPerSample = qMin<quint8>(32, qMax<quint8>(bits_per_sample, 8));
    }
}

bool ExportWorker::get_SignedSamples() {
    return m_SignedSamples;
}

void ExportWorker::set_SignedSamples(bool signed_samples) {
    m_SignedSamples = signed_samples;
}

void ExportWorker::run() {
    
    // Check Member Variables
    
    if (m_File == NULL || m_Buffer == NULL) {
        emit ExportWorker::sig_Done();
        return;
    }
    
    // Open File
    
    if (!m_File->isOpen() && !m_File->open(
        QFile::OpenModeFlag::WriteOnly | QFile::OpenModeFlag::Truncate)) {
        
        qDebug() << "File couldn't be open...";
        
        QFile::FileError error_code = m_File->error();
        
        emit ExportWorker::sig_Error(error_code);
        emit ExportWorker::sig_Done();
        
        return;
    }
    
    // Dump Header
    
    const quint8 WAV_HEADER[44] = {
        0x52, 0x49, 0x46, 0x46, 0xC4, 0x86, 0x01, 0x00, 0x57, 0x41, 0x56, 0x45,
        0x66, 0x6D, 0x74, 0x20, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00,
        0x88, 0x13, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x02, 0x00, 0x10, 0x00,
        0x64, 0x61, 0x74, 0x61, 0xA0, 0x86
    };
    
    m_File->seek(0);
    m_File->write((char*)WAV_HEADER, 44);
    
    // Dump Samples
    
    quint64 chunk_size  = this->calc_ChunkSize(m_Buffer->size());
    quint64 wrote_bytes = 0;
    
    m_File->seek(44);
    
    for (quint64 i = 0; i < m_Buffer->size(); i+=chunk_size) {
        
        QByteArray chunk;
        
        quint64 max_slice = qMin(m_Buffer->size() - i, chunk_size);
        
        chunk += m_Buffer->sliced(i, max_slice);
        
        m_File->write(chunk);
        
        QFile::FileError error_code = m_File->error();
        
        if (error_code != QFile::FileError::NoError) {
            
            m_File->close();
            
            emit ExportWorker::sig_Error(error_code);
            emit ExportWorker::sig_Done();
            
            return;
        }
        
        wrote_bytes += chunk_size;
        
        quint8 progress = (double(wrote_bytes) / m_Buffer->size()) * 100;
        
        emit ExportWorker::sig_Wrote(chunk);
        emit ExportWorker::sig_Progressed(progress);
        
        this->usleep(1000);
    }
    
    // Modify Header
    
    quint8  wav_buffer[4];
    quint64 wav_total_samples;
    quint8  wav_channels;
    quint32 wav_sample_rate;
    quint16 wav_bits_per_sample;
    quint32 wav_byte_rate;
    quint32 wav_subchunk2_size;
    quint32 wav_chunk_size;
    
    wav_total_samples = m_Buffer->size() / (m_BitsPerSample / 8);
    
    m_File->seek(22);
    
    wav_channels = 1;
    wav_buffer[0] = (wav_channels >> 0 ) & 0xFF;
    wav_buffer[1] = (wav_channels >> 8 ) & 0xFF;
    wav_buffer[2] = (wav_channels >> 16) & 0xFF;
    wav_buffer[3] = (wav_channels >> 24) & 0xFF;
    m_File->write((char*)wav_buffer, 2);
    
    m_File->seek(24);
    
    wav_sample_rate = m_SampleRate;
    wav_buffer[0] = (wav_sample_rate >> 0 ) & 0xFF;
    wav_buffer[1] = (wav_sample_rate >> 8 ) & 0xFF;
    wav_buffer[2] = (wav_sample_rate >> 16) & 0xFF;
    wav_buffer[3] = (wav_sample_rate >> 24) & 0xFF;
    m_File->write((char*)wav_buffer, 4);
    
    m_File->seek(34);
    
    wav_bits_per_sample = m_BitsPerSample;
    wav_buffer[0] = (wav_bits_per_sample >> 0 ) & 0xFF;
    wav_buffer[1] = (wav_bits_per_sample >> 8 ) & 0xFF;
    wav_buffer[2] = (wav_bits_per_sample >> 16) & 0xFF;
    wav_buffer[3] = (wav_bits_per_sample >> 24) & 0xFF;
    m_File->write((char*)wav_buffer, 2);
    
    m_File->seek(28);
    
    wav_byte_rate = wav_sample_rate * wav_channels * (wav_bits_per_sample / 8);
    wav_buffer[0] = (wav_byte_rate >> 0 ) & 0xFF;
    wav_buffer[1] = (wav_byte_rate >> 8 ) & 0xFF;
    wav_buffer[2] = (wav_byte_rate >> 16) & 0xFF;
    wav_buffer[3] = (wav_byte_rate >> 24) & 0xFF;
    m_File->write((char*)wav_buffer, 4);
    
    m_File->seek(40);
    
    wav_subchunk2_size = wav_total_samples * wav_channels * (wav_bits_per_sample / 8);
    wav_buffer[0] = (wav_subchunk2_size >> 0 ) & 0xFF;
    wav_buffer[1] = (wav_subchunk2_size >> 8 ) & 0xFF;
    wav_buffer[2] = (wav_subchunk2_size >> 16) & 0xFF;
    wav_buffer[3] = (wav_subchunk2_size >> 24) & 0xFF;
    m_File->write((char*)wav_buffer, 4);
    
    m_File->seek(4);
    
    wav_chunk_size = 36 + wav_subchunk2_size;
    wav_buffer[0] = (wav_chunk_size >> 0 ) & 0xFF;
    wav_buffer[1] = (wav_chunk_size >> 8 ) & 0xFF;
    wav_buffer[2] = (wav_chunk_size >> 16) & 0xFF;
    wav_buffer[3] = (wav_chunk_size >> 24) & 0xFF;
    m_File->write((char*)wav_buffer, 4);
    
    // Finalize The Process
    
    qDebug() << "Channels =" << wav_channels
        << "Sample Rate =" << wav_sample_rate
        << "Bits per Sample =" << wav_bits_per_sample
        << "Byte Rate =" << wav_byte_rate
        << "Subchunk2 Size =" << wav_subchunk2_size
        << "Chunk Size =" << wav_chunk_size;
    
    m_File->close();
    
    emit ExportWorker::sig_Done();
}

