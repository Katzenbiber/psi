#pragma once
#include <string>
#include <vector>

class Settings {
    std::string settings_path;
    void add(std::string variable, std::string value);

  public:
    float c;
    float dx;
    float dt;
    std::vector<float> u;
    std::vector<float> u_prev;
    Settings() = default;
    static Settings default_settings();
    static Settings parse_from_file(const std::string &settings_path);
};
