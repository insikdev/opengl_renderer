#pragma once

#include <string>
#include <fstream>
#include <sstream>

class Utils {
public:
    static std::string LoadTextFromFile(std::string filename)
    {
        std::ifstream fin(filename);

        if (!fin.is_open()) {
            SPDLOG_ERROR("Failed to open file : {} ", filename);
            exit(EXIT_FAILURE);
        }

        std::stringstream text;
        text << fin.rdbuf();
        return text.str();
    }
};
