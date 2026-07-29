#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "fileUtils.h"
#include "lcs.h"

int main()
{
    std::string filePrefix = "./input/Strings";
    std::string fileSufix = ".txt";
    std::vector<std::string> fileList = {"10", "12", "14", "16", "18", "20", "25", "50",
                                         "100", "150", "200", "300", "500", "750", "1000",
                                         "1500", "2000", "3000", "5000", "7500", "10000"};

    std::ofstream CSVfilePD;
    auto startPD = PrepareCsvOutput("resultadosPD_lcs.csv",
                                     "Tamanho;Tempo_PD_Segundos;\n",
                                     fileList,
                                     CSVfilePD);

    if (!startPD) {
        return 1;
    }

    for (std::size_t k = *startPD; k < fileList.size(); ++k) {
        const auto& strsize = fileList[k];

        std::string fileName = filePrefix + strsize + fileSufix;
        std::ifstream file(fileName);
        std::string str1;
        std::string str2;

        ReadFiles(file, str1, str2);
        int reps = 6;

        double soma_pd = 0.0;

        for (int i = 0; i < reps; ++i) {
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
            std::cout << "Tamanho da LCS: " << table[n][m] << '\n';
            std::cout << "LCS: " << lcs << '\n';
            std::cout << "Tempo decorrido: " << duracao.count() << " s\n";
        }

        double media_pd = soma_pd / (reps - 1);

        CSVfilePD << strsize << ";" << media_pd << "\n";
        CSVfilePD.flush();
        std::cout << "Tamanho " << strsize << " concluido.\n";
    }

    CSVfilePD.close();

    std::ofstream CSVfileREC;
    auto startREC = PrepareCsvOutput("resultadosREC_lcs.csv",
                                      "Tamanho;Tempo_REC_Segundos;\n",
                                      fileList,
                                      CSVfileREC);

    if (!startREC) {
        return 1;
    }

    std::cout << "Iniciando execucao do algoritmo recursivo a partir do tamanho: "
              << fileList[*startREC] << '\n';

    for (std::size_t k = *startREC; k < fileList.size(); ++k) {
        const auto& strsize = fileList[k];
        std::string fileName = filePrefix + strsize + fileSufix;
        std::ifstream file(fileName);
        std::string str1;
        std::string str2;

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



   
   