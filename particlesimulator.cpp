#include "particlesimulator.h"

ParticleSimulator::ParticleSimulator()
{    
    num_particles = 100;
    par = new Particle[100];
}

ParticleSimulator::ParticleSimulator(int n)
{
    num_particles = n;
    par = new Particle[n];
}

void ParticleSimulator::set_num_particles(int n){
    num_particles = n;
}

unsigned int ParticleSimulator::get_num_particles(){
    return num_particles;
}
