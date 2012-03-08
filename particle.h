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
