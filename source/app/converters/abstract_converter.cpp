#include "abstract_converter.h"

void AbstractConverter::set_Signed(bool value) {
    m_Signed = value;
}

bool AbstractConverter::get_Signed() {
    return m_Signed;
}

void AbstractConverter::set_ConversionType(AbstractConverter::Type value) {
    m_Type = value;
}

AbstractConverter::Type AbstractConverter::get_ConversionType() {
    return m_Type;
}
