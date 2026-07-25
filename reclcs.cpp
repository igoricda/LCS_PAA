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
        std::cerr << "Error opening file!" << std::endl;
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


int main() {


    std::ifstream file("./input/Strings10.txt");
    std::string str1 = "";
    std::string str2 = "";
    std::string lcs = "";

    ReadFiles(file, str1, str2);

    std::cout << "String 1: " << str1 << '\n' << "\nString 2:" << str2 << '\n'; 

    int ans = recLCS(str1, str2, str1.length(), str2.length());

    std::cout << "\nTamanho da LCS: " << ans << '\n';


   return 0;
}
