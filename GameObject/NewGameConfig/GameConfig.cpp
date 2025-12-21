#include "GameConfig.h"
#include "ConfigKeyMap.h"
#include <fstream>
#include <iostream>

GameConfig& GameConfig::instance() {
    static GameConfig inst;
    return inst;
}

void GameConfig::loadFromFile(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Khong the mo file config: " << path << '\n';
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        auto pos = line.find('=');
        if (pos == string::npos) continue;

        string key = line.substr(0, pos);
        string value = line.substr(pos + 1);

        m_values[key] = value;
    }
}

int GameConfig::getInt(ConfigKey key) const {
    const auto& strKey = ConfigKeyToString.at(key);
    return stoi(m_values.at(strKey));
}

float GameConfig::getFloat(ConfigKey key) const {
    const auto& strKey = ConfigKeyToString.at(key);
    return stof(m_values.at(strKey));
}
