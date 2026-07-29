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

    int i = str1.length();
    int j = str2.length();

    std::string lcs = recLCS(str1, str2, i, j);

    std::cout << "\nTamanho da LCS: " << lcs.length() << '\n';
    std::cout << "LCS: " << lcs << '\n';

    return 0;
}
