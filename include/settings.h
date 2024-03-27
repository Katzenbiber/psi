#pragma once
#include <string>
#include <vector>

class Settings {
    std::string settings_path;

  public:
    float c;
    float dx;
    float dt;
    std::vector<float> u;
    std::vector<float> u_prev;
    Settings();
    static Settings parse_from_file(std::basic_string<char> settings_path);
};
