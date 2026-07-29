#ifndef LCS_H
#define LCS_H

#include <string>
#include <vector>

std::string recLCS(const std::string& str1,
                   const std::string& str2,
                   int i,
                   int j);

std::vector<std::vector<int>> PD_LCS(const std::string& str1,
                                     const std::string& str2);

std::string STR_LCS(const std::string& str1,
                    const std::string& str2,
                    const std::vector<std::vector<int>>& table);

#endif
