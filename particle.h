#ifndef PARTICLE_H
#define PARTICLE_H

#include <QVector3D>
#include <QGLWidget>

class Particle
{
public:
    Particle();
    Particle(int particle_mass);
    void SetPosition(QVector3D vec);
    QVector3D Get_Position();

    void SetColour(QVector3D vec);
    QVector3D Get_Colour();

private:
    QVector3D position;
    QVector3D colour;
    GLfloat mass;

};

#endif // PARTICLE_H
