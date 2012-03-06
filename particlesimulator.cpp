#include "particlesimulator.h"

ParticleSimulator::ParticleSimulator()
{    
    num_particles = 0;
}

ParticleSimulator::ParticleSimulator(int n)
{
    num_particles = n;
}

void ParticleSimulator::set_num_particles(int n){
    num_particles = n;
}

int ParticleSimulator::get_num_particles(){
    return num_particles;
}

int RandomMovement()
{

}
