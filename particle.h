#ifndef PARTICLE_H
#define PARTICLE_H

#include <QVector3D>

class Particle
{
public:
    Particle();
    void SetPosition(QVector3D vec);
    QVector3D Get_Position();

    void SetColour(QVector3D vec);
    QVector3D Get_Colour();

private:
    QVector3D position;
    QVector3D colour;

};

#endif // PARTICLE_H
