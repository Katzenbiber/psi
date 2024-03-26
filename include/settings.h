#include <string>

class Settings {
    std::string settings_path;
    float c;
    float dx;
    float dt;

  public:
    Settings();
    static Settings parse_from_file(std::basic_string<char> settings_path);
};
