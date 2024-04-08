#include "simulation.h"
#include <iostream>
#include <vector>

Simulation::Simulation(const Settings &settings) {
    // initialize simulation
    time = 0.0;
    dx = settings.dx;
    c = settings.c;
    u = settings.u;
    u_prev = settings.u_prev;
}

void Simulation::visualize() {
    // make cursor invisible
    // if you are interested in details:
    // https://en.wikipedia.org/wiki/ANSI_escape_code#CSI_(Control_Sequence_Introducer)_sequences
    std::cout << "\033[?25l";
    // visualize
    // BUG: don't visualize all lines
    for (int row = 5; row > -7; row--) {
        for (int i = 0; i < u.size(); i++) {
            if (u[i] >= row && u[i] < row + 1) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    // move cursor up by 11 lines
    std::cout << "\033[12A";
}

void Simulation::step(float dt) {
    // step forward in simulation
    time += dt;
    std::vector<float> u_next;
    // preallocate memory for u_next
    u_next.reserve(u.size());

    for (int i = 0; i < u.size(); i++) {
        // BUG: forget to handle boundary conditions
        float left = i == 0 ? 0 : u[i - 1];
        float right = i == u.size() - 1 ? 0 : u[i + 1];

        float u_xx = (left - 2 * u[i] + right) / (dx * dx);
        float u_new = c * c * u_xx * dt * dt + 2 * u[i] - u_prev[i];
        u_next.push_back(u_new);
    }

    u_prev = u;
    u = u_next;
}
