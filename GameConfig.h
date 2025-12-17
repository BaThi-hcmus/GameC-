#pragma once
#include <string>
#include <unordered_map>

class GameConfig {
public:
    static GameConfig& instance();

    void loadFromFile(const std::string& path);

    int    getInt(const std::string& key) const;
    float  getFloat(const std::string& key) const;

private:
    GameConfig() = default;

    std::unordered_map<std::string, std::string> m_values;
};
