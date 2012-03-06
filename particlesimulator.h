#ifndef PARTICLESIMULATOR_H
#define PARTICLESIMULATOR_H

#include "particle.h"

#define MAX_NUM_PARTICLES 100

class ParticleSimulator
{
public:
    /* Variables */
    Particle par[MAX_NUM_PARTICLES];
    void set_num_particles(int n);
    int get_num_particles();

    /* Funcions */
    ParticleSimulator();
    ParticleSimulator(int n);

private:
    unsigned int num_particles;
};

#endif // PARTICLESIMULATOR_H
