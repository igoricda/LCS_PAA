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

//Implementação recursiva, usando tabela para possibilitar backtracking
int recLCSTable(const std::string& str1,
           const std::string& str2,
           int i,
           int j,
           std::vector<std::vector<int>>& table){
    if(!i || !j)
        return 0;
    if(table[i][j] != 0)
        return table[i][j];
    if(i && j  && str1[i-1] == str2[j-1])
        table[i][j] = 1 + recLCSTable(str1, str2, i-1, j-1, table);
    else
        table[i][j] =  std::max(recLCSTable(str1, str2, i - 1, j, table),
                        recLCSTable(str1, str2, i, j - 1, table));
                
    return table[i][j];
}

//Implementação recursiva, retornando somente o tamanho
int recLCS(const std::string& str1,
           const std::string& str2,
           int i,
           int j){
    if(!i || !j){
        return 0;
    }
    if(i && j  && str1[i-1] == str2[j-1]){
        return 1 + recLCS(str1, str2, i-1, j-1);
    } 
    return std::max(recLCS(str1, str2, i - 1, j),
                    recLCS(str1, str2, i, j - 1));
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

    int i = str1.length();
    int j = str2.length();

    std::vector<std::vector<int>> table(i + 1, std::vector<int>(j + 1, -1));
    int ans = recLCSTable(str1, str2, str1.length(), str2.length(), table);
    std::string lcs = STR_LCS(str1, str2, table);

    std::cout << "\nTamanho da LCS: " << ans << '\n';
    std::cout << "LCS: " << lcs << '\n';


   return 0;
}
