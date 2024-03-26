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
    void visualize();
    void step(float dt);
};
