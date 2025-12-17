#include "GameConfig.h"
#include <fstream>
#include <sstream>
#include <iostream>

GameConfig& GameConfig::instance() {
    static GameConfig inst;
    return inst;
}

void GameConfig::loadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Khong the mo file config: " << path << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        auto pos = line.find('=');
        if (pos == std::string::npos) continue;

        std::string key   = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        m_values[key] = value;
    }

    std::cout << "[GameConfig] Da load xong config.\n";
    std::cout << "Cac gia tri hien tai:\n";
    for (auto& [k, v] : m_values) {
        std::cout << "[" << k << "] = " << v << '\n';
    }
}

int GameConfig::getInt(const std::string& key) const {
    return std::stoi(m_values.at(key));
}

float GameConfig::getFloat(const std::string& key) const {
    return std::stof(m_values.at(key));
}
