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
    unsigned int num_particles;

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

    unsigned int mode;
};

#endif // PARTICLESIMULATOR_H
