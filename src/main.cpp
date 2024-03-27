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
        std::basic_string<char> settings_path =
            std::basic_string<char>(argv[1]);
        std::cout << "Settings path: " << settings_path << std::endl;
        //  TODO: parse input file
        //        - simulation parameters
        //        - initial conditions
        // Settings settings = Settings::parse_from_file(settings_path);
    } else {
        std::cout << "Using default settings" << std::endl;
        settings.c = 10.0;
        settings.dx = 1.0;
        settings.dt = 0.1;
        settings.u = std::vector<float>(101, 0.0);
        settings.u_prev = std::vector<float>(101, 0.0);
        for (int i = 0; i < settings.u.size(); i++) {
            settings.u[i] = sin(i * M_PI / 100.0) * 5;
        }
        for (int i = 0; i < settings.u_prev.size(); i++) {
            settings.u_prev[i] = sin(i * M_PI / 100.0) * 5;
        }
    }

    // initialize simulation
    // TODO: pass simulation parameters and initial conditions
    Simulation sim = Simulation(settings);

    std::cout << "Starting simulation, press Ctrl-C / Strg-C to exit"
              << std::endl;

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
