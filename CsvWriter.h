#pragma once

#include <string>
#include <vector>
#include <fstream>

class CsvWriter {
public:
    explicit CsvWriter(const std::string& filename);
    ~CsvWriter();
    
    bool isOpen() const;
    void writeHeader(const std::vector<std::string>& headers);
    void writeRow(const std::vector<std::string>& data);
    void close();

private:
    std::ofstream m_file;
    bool m_isOpen;
}; 