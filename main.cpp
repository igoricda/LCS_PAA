#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype> 
#include <cstring>
#include <cmath>
#include <vector>
#include <chrono>
#include <iomanip>

#include <filesystem>
#include <set>

#include <optional>

std::optional<std::string> LastSize(const std::string& nomeCSV)
{
    std::ifstream arq(nomeCSV);

    if (!arq.is_open())
        return std::nullopt;

    std::string linha;
    std::string ultima;

    std::getline(arq, linha);

    while (std::getline(arq, linha))
    {
        if (!linha.empty())
            ultima = linha;
    }

    if (ultima.empty())
        return std::nullopt;

    return ultima.substr(0, ultima.find(';'));
}


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


    std::string filePrefix = "./input/Strings";
    std::string fileSufix = ".txt";
    std::vector<std::string> fileList = {"10", "12", "14", "16", "18", "20", "25", "50",
                                         "100", "150", "200", "300", "500", "750", "1000",
                                         "1500", "2000", "3000", "5000", "7500", "10000"}; 

    
    bool existePD = std::filesystem::exists("resultadosPD_lcs.csv");

    std::ofstream CSVfilePD(
        "resultadosPD_lcs.csv",
        std::ios::app
    );

    if (!CSVfilePD.is_open()) {
        std::cerr << "Erro ao criar o arquivo CSV!\n";
        return 1;
    }

    if (!existePD) {
        CSVfilePD << "Tamanho;Tempo_PD_Segundos;\n";
        CSVfilePD << std::scientific << std::setprecision(6);
    }

    size_t startPD = 0;

    auto ultimoPD = LastSize("resultadosPD_lcs.csv");
    if (ultimoPD) {
        auto it = std::find(fileList.begin(), fileList.end(), *ultimoPD);

        if (it != fileList.end())
            startPD = std::distance(fileList.begin(), it) + 1;
    }


    
    
    for (size_t k = startPD; k < fileList.size(); k++){

        const auto& strsize = fileList[k];

        std::string fileName = filePrefix + strsize + fileSufix;
        std::ifstream file(fileName);
        std::string str1 = "";
        std::string str2 = "";

        ReadFiles(file, str1, str2);
        int reps = 6;

        double soma_pd = 0.0;

        for(int i = 0; i < reps; i++){
            int n = str1.length();
            int m = str2.length();

            

            auto inicio = std::chrono::steady_clock::now();
            auto table = PD_LCS(str1, str2);

            std::string lcs = STR_LCS(str1, str2, table);
            auto fim = std::chrono::steady_clock::now();
            std::chrono::duration<double> duracao = fim - inicio;
            if (i > 0) {
                soma_pd += duracao.count();
            }
            std::cout << "\nTamanho da string: " << strsize << '\n';
            std::cout << "Tamanho da LCS: "
                        << table[n][m] << '\n';

            std::cout << "LCS: " << lcs << '\n';
            std::cout << "Tempo decorrido: " << duracao.count() << " s\n";
        }
         double media_pd = soma_pd / (reps - 1);

        CSVfilePD << strsize << ";" << media_pd << "\n";
        CSVfilePD.flush(); 
        std::cout << "Tamanho " << strsize << " concluido.\n";
    }

    CSVfilePD.close();
    

    bool existeREC = std::filesystem::exists("resultadosREC_lcs.csv");

    std::ofstream CSVfileREC(
        "resultadosREC_lcs.csv",
        std::ios::app
    );

    if (!CSVfileREC.is_open()) {
        std::cerr << "Erro ao criar o arquivo CSV!\n";
        return 1;
    }

    if (!existeREC) {
        CSVfileREC << "Tamanho;Tempo_REC_Segundos;\n";
        CSVfileREC << std::scientific << std::setprecision(6);
    }

    size_t startREC = 0;

    auto ultimoREC = LastSize("resultadosREC_lcs.csv");

    if (ultimoREC) {
        auto it = std::find(fileList.begin(), fileList.end(), *ultimoREC);

        if (it != fileList.end())
            startREC = std::distance(fileList.begin(), it) + 1;
    }

    std::cout << "Iniciando execucao do algoritmo recursivo a partir do tamanho: " << fileList[startREC] << '\n';

    
    for (size_t k = startREC; k < fileList.size(); k++) {

        const auto& strsize = fileList[k];
        std::string fileName = filePrefix + strsize + fileSufix;
        std::ifstream file(fileName);
        std::string str1 = "";
        std::string str2 = "";

        ReadFiles(file, str1, str2);

        int reps = 6;
        double soma_rec = 0.0;

        for(int i = 0; i < reps; i++){

            int n = str1.length();
            int m = str2.length();

            auto inicio = std::chrono::steady_clock::now();
            std::string lcs = recLCS(str1, str2, n, m);
            auto fim = std::chrono::steady_clock::now();
            std::chrono::duration<double> duracao = fim - inicio;
            if (i > 0) {
                soma_rec += duracao.count();
            }
            std::cout << "\nTamanho da string: " << strsize << '\n';
            std::cout << "Tamanho da LCS: " << lcs.length() << '\n';
            std::cout << "LCS: " << lcs << '\n';
            std::cout << "Tempo decorrido: " << duracao.count() << " s\n";
        }
        
        double media_rec = soma_rec / (reps - 1);

        CSVfileREC << strsize << ";" << media_rec << "\n";
        CSVfileREC.flush(); 
        std::cout << "Tamanho " << strsize << " concluido.\n";
    }
    CSVfileREC.close();
   return 0;
}



   
   