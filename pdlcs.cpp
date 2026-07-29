#include <fstream>
#include <iostream>
#include <string>

#include "fileUtils.h"
#include "lcs.h"

int main()
{
    std::ifstream file("./input/Strings18.txt");
    std::string str1;
    std::string str2;

    ReadFiles(file, str1, str2);

    std::cout << "String 1: " << str1 << '\n' << "\nString 2:" << str2 << '\n';

    auto table = PD_LCS(str1, str2);
    std::string lcs = STR_LCS(str1, str2, table);

    std::cout << "\nTamanho da LCS: " << table[str1.length()][str2.length()] << '\n';
    std::cout << "LCS: " << lcs << '\n';

    return 0;
}
