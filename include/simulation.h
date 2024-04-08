#pragma once
#include "settings.h"
#include <vector>

class Simulation {
  private:
    float time;
    float dx;
    float c;
    std::vector<float> u;
    std::vector<float> u_prev;

  public:
    Simulation();
    Simulation(const Settings &settings);
    void visualize();
    void step(float dt);
};
