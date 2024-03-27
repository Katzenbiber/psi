#include "settings.h"
#include <fstream>
#include <iostream>
#include <sstream>

Settings::Settings() {}
Settings Settings::parse_from_file(std::basic_string<char> settings_path) {
    Settings settings;
    std::ifstream settings_file(settings_path);

    std::string variable, equal, value;
    while ((settings_file >> variable >> equal >> value) && (equal == "=")) {
        if (value[0] == '[') {
            // TODO: parse array
            while (value.back() != ']') {
                std::string next_value;
                settings_file >> next_value;
                value += " " + next_value;
            }
            settings.add(variable, value);
        } else {
            settings.add(variable, value);
        }
    }

    return settings;
}

std::vector<float> parse_array(std::string array) {
    // remove '[' and ']'
    array = array.substr(1, array.size() - 2);
    std::stringstream ss(array);
    std::vector<float> vec;
    std::string value;
    while (ss >> value) {
        // ignore commas
        if (value == ",") {
            continue;
        }
        if (value.back() == ',') {
            value.pop_back();
        }
        vec.push_back(std::stof(value));
    }
    return vec;
}

void Settings::add(std::string variable, std::string value) {
    if (variable == "c") {
        c = std::stof(value);
    } else if (variable == "dx") {
        dx = std::stof(value);
    } else if (variable == "dt") {
        dt = std::stof(value);
    } else if (variable == "u") {
        u = parse_array(value);
    } else if (variable == "u_prev") {
        u_prev = parse_array(value);
    } else {
        std::cout << "Unknown variable: " << variable << std::endl;
    }
}
