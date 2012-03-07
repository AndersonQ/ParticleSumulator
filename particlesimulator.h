#ifndef PARTICLESIMULATOR_H
#define PARTICLESIMULATOR_H

#include "particle.h"

#define MAX_NUM_PARTICLES 10000

class ParticleSimulator
{
public:
    /* Variables */
    Particle par[MAX_NUM_PARTICLES];


    /* Funcions */
    ParticleSimulator();
    ParticleSimulator(int n);
    void set_num_particles(int n);
    int get_num_particles();

private:
    unsigned int num_particles;
};

#endif // PARTICLESIMULATOR_H
