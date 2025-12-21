#pragma once
#include <unordered_map>
#include <string>
#include "ConfigKey.h"

using namespace std;

class GameConfig {
public:
    static GameConfig& instance();

    void loadFromFile(const std::string& path);

    int   getInt(ConfigKey key) const;
    float getFloat(ConfigKey key) const;

private:
    GameConfig() = default;

    std::unordered_map<std::string, std::string> m_values;
};
