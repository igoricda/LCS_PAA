#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

std::optional<std::string> LastSize(const std::string& nomeCSV);

void ReadFiles(std::ifstream& file, std::string& outLine1, std::string& outLine2);

std::optional<std::size_t> PrepareCsvOutput(const std::string& csvPath,
                                            const std::string& header,
                                            const std::vector<std::string>& fileList,
                                            std::ofstream& csvFile);

#endif
