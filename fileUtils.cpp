#include "fileUtils.h"

std::optional<std::string> LastSize(const std::string& nomeCSV)
{
    std::ifstream arq(nomeCSV);

    if (!arq.is_open()) {
        return std::nullopt;
    }

    std::string linha;
    std::string ultima;

    std::getline(arq, linha);

    while (std::getline(arq, linha)) {
        if (!linha.empty()) {
            ultima = linha;
        }
    }

    if (ultima.empty()) {
        return std::nullopt;
    }

    return ultima.substr(0, ultima.find(';'));
}

void ReadFiles(std::ifstream& file, std::string& outLine1, std::string& outLine2)
{
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

std::optional<std::size_t> PrepareCsvOutput(const std::string& csvPath,
                                            const std::string& header,
                                            const std::vector<std::string>& fileList,
                                            std::ofstream& csvFile)
{
    bool existe = std::filesystem::exists(csvPath);

    csvFile.open(csvPath, std::ios::app);

    if (!csvFile.is_open()) {
        std::cerr << "Erro ao criar o arquivo CSV!\n";
        return std::nullopt;
    }

    if (!existe) {
        csvFile << header;
        csvFile << std::scientific << std::setprecision(6);
    }

    std::size_t start = 0;

    auto ultimo = LastSize(csvPath);
    if (ultimo) {
        auto it = std::find(fileList.begin(), fileList.end(), *ultimo);

        if (it != fileList.end()) {
            start = std::distance(fileList.begin(), it) + 1;
        }
    }

    return start;
}
