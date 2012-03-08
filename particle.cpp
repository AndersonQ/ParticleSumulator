#include "particle.h"

Particle::Particle()
{
    mass = 5;
}

Particle::Particle(int particle_mass)
{
    mass = particle_mass;
}

void Particle::SetPosition(QVector3D vec){
    position = vec;
}

QVector3D Particle::Get_Position()
{
    return position;
}

void Particle::SetColour(QVector3D vec){
    colour = vec;
}

QVector3D Particle::Get_Colour()
{
    return colour;
}

void Particle::SetMass(GLfloat m){
    mass = m;
}

GLfloat Particle::Get_Mass(){
    return mass;
}

/*
void Particle::SetResult_force(QVector3D force){
    result_force = force;
}

QVector3D Particle::Get_Result_force(){
    return result_force;
}*/
