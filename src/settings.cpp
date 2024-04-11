#include "settings.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

Settings Settings::default_settings() {
    Settings settings;
    settings.c = 10.0;
    settings.dx = 1.0;
    settings.dt = 0.1;
    settings.u = std::vector<float>(101, 0.0);
    for (int i = 0; i < settings.u.size(); i++) {
        settings.u[i] = sin(i * M_PI / 100.0) * 5;
    }
    return settings;
}

Settings Settings::parse_from_file(const std::string &settings_path) {
    Settings settings;
    settings.settings_path = settings_path;
    std::ifstream settings_file(settings_path);

    std::string variable, equal, value;
    while ((settings_file >> variable >> equal >> value) && (equal == "=")) {
        if (value[0] == '[') {
            // parse array
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

void Settings::add(const std::string variable, std::string value) {
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
