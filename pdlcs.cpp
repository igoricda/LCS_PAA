#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype> 
#include <cstring>
#include <cmath>
#include <vector>


void ReadFiles(std::ifstream &file, std::string &outLine1, std::string &outLine2){
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return;
    }
    
    std::getline(file, outLine1);
    outLine1.erase(std::remove_if(outLine1.begin(), outLine1.end(), [](unsigned char x) { 
        return std::isspace(x); 
    }), outLine1.end());

    std::getline(file, outLine2);
    outLine2.erase(std::remove_if(outLine2.begin(), outLine2.end(), [](unsigned char x) { 
        return std::isspace(x); 
    }), outLine2.end());

    file.close();
}

//Implementação usando Programação dinâmica
std::vector<std::vector<int>> PD_LCS(const std::string& str1,
                                     const std::string& str2)
{
    int n = str1.length();
    int m = str2.length();

    std::vector<std::vector<int>> table(n + 1, std::vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (str1[i - 1] == str2[j - 1])
                table[i][j] = table[i - 1][j - 1] + 1;
            else
                table[i][j] = std::max(table[i - 1][j], table[i][j - 1]);
        }
    }

    return table;
}

//Backtracking pela tabela
std::string STR_LCS(const std::string& str1,
                    const std::string& str2,
                    const std::vector<std::vector<int>>& table)
{
    std::string lcs;

    int i = str1.length();
    int j = str2.length();

    while (i > 0 && j > 0)
    {
        if (str1[i - 1] == str2[j - 1])
        {
            lcs.insert(0, 1, str1[i - 1]);
            i--;
            j--;
        }
        else if (table[i - 1][j] >= table[i][j - 1])
            i--;
        else
            j--;
    }

    return lcs;
}

int main() {


    std::ifstream file("./input/Strings10000.txt");
    std::string str1 = "";
    std::string str2 = "";

    ReadFiles(file, str1, str2);

    std::cout << "String 1: " << str1 << '\n' << "\nString 2:" << str2 << '\n'; 

    auto table = PD_LCS(str1, str2);

    std::string lcs = STR_LCS(str1, str2, table);

    std::cout << "\nTamanho da LCS: "
            << table[str1.length()][str2.length()] << '\n';

    std::cout << "LCS: " << lcs << '\n';
   

   return 0;
}
