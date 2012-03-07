#ifndef PARTICLESIMULATOR_H
#define PARTICLESIMULATOR_H

#include "particle.h"

class ParticleSimulator
{
public:
    /* Variables */
    Particle *par;
    Particle *blackhole;
    Particle *whitehole;

    /* Funcions */
    ParticleSimulator();
    ParticleSimulator(int n);
    void set_num_particles(int n);
    unsigned int get_num_particles();

private:
    unsigned int num_particles;
};

#endif // PARTICLESIMULATOR_H
