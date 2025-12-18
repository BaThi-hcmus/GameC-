#include "GameConfig.h"
#include "ConfigKeyMap.h"
#include <fstream>
#include <iostream>

GameConfig& GameConfig::instance() {
    static GameConfig inst;
    return inst;
}

void GameConfig::loadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Khong the mo file config: " << path << '\n';
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        auto pos = line.find('=');
        if (pos == std::string::npos) continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        m_values[key] = value;
    }
}

int GameConfig::getInt(ConfigKey key) const {
    const auto& strKey = ConfigKeyToString.at(key);
    return std::stoi(m_values.at(strKey));
}

float GameConfig::getFloat(ConfigKey key) const {
    const auto& strKey = ConfigKeyToString.at(key);
    return std::stof(m_values.at(strKey));
}
