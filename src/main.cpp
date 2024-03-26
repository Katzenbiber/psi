#include "settings.h"
#include "simulation.h"
#include <iostream>
#include <string>
#include <thread>

int main(int argc, char **argv) {
    // BUG: forget to check if input file is provided
    std::basic_string<char> settings_path = std::basic_string<char>(argv[1]);
    std::cout << "Settings path: " << settings_path << std::endl;

    //  TODO: parse input file
    //        - simulation parameters
    //        - initial conditions
    // Settings settings = Settings::parse_from_file(settings_path);

    // initialize simulation
    // TODO: pass simulation parameters and initial conditions
    Simulation sim = Simulation();

    // loop
    for (;;) {
        // visualize
        sim.visualize();

        // step forward in simulation
        sim.step(0.1);

        // sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
