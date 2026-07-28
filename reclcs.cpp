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


//Implementação recursiva, retornando somente o tamanho


std::string recLCS(const std::string& str1,
           const std::string& str2,
           int i,
           int j){

            if (!i || !j){
                return "";
            }
            if(str1[i-1] == str2[j-1]){
                return recLCS(str1, str2, i-1, j-1) + str1[i-1];
            }
            std::string lcs1 = recLCS(str1, str2, i-1, j);
            std::string lcs2 = recLCS(str1, str2, i, j-1);
            
            return (lcs1.length() > lcs2.length()) ? lcs1 : lcs2;

}

int main() {


    std::ifstream file("./input/Strings18.txt");
    std::string str1 = "";
    std::string str2 = "";
    

    ReadFiles(file, str1, str2);

    
    std::cout << "String 1: " << str1 << '\n' << "\nString 2:" << str2 << '\n'; 

    int i = str1.length();
    int j = str2.length();

    //tinit
    std::string lcs = recLCS(str1, str2, i, j);
    //tfim
    
    std::cout << "\nTamanho da LCS: " << lcs.length() << '\n';
    std::cout << "LCS: " << lcs << '\n';


   return 0;
}
