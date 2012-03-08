/*
 * This file is part of Simulador_de_Particulas.
 *
 * Simulador_de_Particulas is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Simulador_de_Particulas is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Simulador_de_Particulas.  If not, see <http://www.gnu.org/licenses/>.
 */

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
