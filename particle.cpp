#include "particle.h"

Particle::Particle()
{
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
