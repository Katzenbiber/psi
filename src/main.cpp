#include "simulation.h"
#include <thread>

int main() {
    // TODO: implement command line argument parsing
    //       - input file

    //  TODO: parse input file
    //        - simulation parameters
    //        - initial conditions

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
