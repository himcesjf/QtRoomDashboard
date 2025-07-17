#include "CsvWriter.h"
#include <sstream>

CsvWriter::CsvWriter(const std::string& filename) : m_isOpen(false) {
    m_file.open(filename);
    m_isOpen = m_file.is_open();
}

CsvWriter::~CsvWriter() {
    close();
}

bool CsvWriter::isOpen() const {
    return m_isOpen;
}

void CsvWriter::writeHeader(const std::vector<std::string>& headers) {
    if (!m_isOpen) return;
    
    for (size_t i = 0; i < headers.size(); ++i) {
        if (i > 0) m_file << ",";
        m_file << headers[i];
    }
    m_file << std::endl;
    m_file.flush();
}

void CsvWriter::writeRow(const std::vector<std::string>& data) {
    if (!m_isOpen) return;
    
    for (size_t i = 0; i < data.size(); ++i) {
        if (i > 0) m_file << ",";
        m_file << data[i];
    }
    m_file << std::endl;
    m_file.flush();
}

void CsvWriter::close() {
    if (m_isOpen) {
        m_file.close();
        m_isOpen = false;
    }
} 