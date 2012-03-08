#ifndef PARTICLESIMULATOR_H
#define PARTICLESIMULATOR_H

#include "particle.h"
#include <math.h>

#include <stdio.h>

class ParticleSimulator
{
public:
    /* Variables */
    Particle *par;
    Particle *blackhole;
    Particle *whitehole;
    int dt;

    /* Funcions */
    ParticleSimulator();
    ParticleSimulator(int n);
    void set_num_particles(int n);
    unsigned int get_num_particles();
    void set_mode(int n);
    unsigned int get_mode();
    void Gravitation();
    void MoveParticles();
    void WhiteHole();
    void GoB();

private:
    unsigned int num_particles;
    unsigned int mode;
};

#endif // PARTICLESIMULATOR_H
