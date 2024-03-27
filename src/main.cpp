#include "settings.h"
#include "simulation.h"
#include <iostream>
#include <string>
#include <csignal>
#include <thread>

void exit_handler(int s) {
    // move curser down 12 lines
    std::cout << "\033[12B" << std::endl;
    // make cursor visible again
    std::cout << "\033[?25h" << std::endl;
    std::cout << "Exiting..." << std::endl;
    exit(1);
}

int main(int argc, char **argv) {
    // register exit handler
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = exit_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);

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

    std::cout << "Starting simulation, press Ctrl-C / Strg-C to exit" << std::endl;

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
