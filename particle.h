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

#ifndef PARTICLE_H
#define PARTICLE_H

#include <QVector3D>
#include <QGLWidget>

class Particle
{
public:
    /* Functions */
    Particle();
    Particle(int particle_mass);

    void SetPosition(QVector3D vec);
    QVector3D Get_Position();
    void SetColour(QVector3D vec);
    QVector3D Get_Colour();
    /*void SetResult_force(QVector3D force);
    QVector3D Get_Result_force();*/
    void SetMass(GLfloat m);
    GLfloat Get_Mass();

    /* Variables */
    QVector3D result_force;

private:
    /* Variables */
    QVector3D position;
    QVector3D colour;
    GLfloat mass;

};

#endif // PARTICLE_H
