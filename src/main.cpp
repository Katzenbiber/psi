#include "settings.h"
#include "simulation.h"
#include <cmath>
#include <csignal>
#include <iostream>
#include <string>
#include <thread>

void exit_handler(int s) {
    // move cursor down 12 lines
    std::cout << "\033[12B" << std::endl;
    // make cursor visible again
    std::cout << "\033[?25h" << std::endl;
    std::cout << "Exiting..." << std::endl;
    exit(0);
}

int main(int argc, char **argv) {
    // register exit handler
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = exit_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);

    // BUG: forget to check if input file is provided
    Settings settings;
    if (argc >= 2) {
        std::string settings_path = std::string(argv[1]);
        std::cout << "Settings path: " << settings_path << std::endl;
        settings = Settings::parse_from_file(settings_path);
    } else {
        std::cout << "Using default settings" << std::endl;
        settings = Settings::default_settings();
    }

    // initialize simulation
    Simulation sim = Simulation(settings);

    std::cout << "Starting simulation, press Ctrl-C / Strg-C to exit"
              << std::endl;

    // loop
    for (;;) {
        // visualize
        sim.visualize();

        // step forward in simulation
        sim.step(settings.dt);

        // sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
