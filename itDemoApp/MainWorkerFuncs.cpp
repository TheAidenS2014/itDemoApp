#include "pch.h"
#include "MainWorkerFuncs.h"

std::vector<std::string> fetchLabelsFromFile(const std::string& filename)
{
    std::vector<std::string> labels;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        labels.push_back(line);
    }
    return labels;
}