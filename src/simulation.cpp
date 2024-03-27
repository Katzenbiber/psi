#include "simulation.h"
#include <cmath>
#include <iostream>
#include <vector>

Simulation::Simulation() {
    // initialize simulation
    time = 0.0;
    // BUG: forget to initialize u_prev
    u_prev = std::vector<float>(101, 0.0);
    u = std::vector<float>(101, 0.0);
    dx = 1;
    c = 10.0;

    // initialize u with half a sine wave
    for (int i = 0; i < u.size(); i++) {
        u[i] = sin(i * M_PI / 100.0) * 5;
    }
    for (int i = 0; i < u.size(); i++) {
        u_prev[i] = sin(i * M_PI / 100.0) * 5;
    }
}

void Simulation::visualize() {
    // visualize
    for (int row = 5; row > -6; row--) {
        for (int i = 0; i < u.size(); i++) {
            if (u[i] >= row && u[i] < row + 1) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "\033[11A";
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
