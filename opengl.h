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

#ifndef OPENGL_H
#define OPENGL_H

#include <QGLWidget>

#include <QGLShader>
#include <QGLShaderProgram>
#include <QGLBuffer>
#include <QMatrix4x4>
#include <QVector3D>

#include <particle.h>
#include <particlesimulator.h>
#include <QTimer>

class OpenGL : public QGLWidget
{
    Q_OBJECT
public:
    explicit OpenGL(QWidget *parent = 0);

signals:

public slots:
    void Step();
    void xslot(int n);
    void yslot(int n);
    void zslot(int n);
    void zoomslot(int n);
    void set_num_particles(int n);
    void stepbt();
    void startbt();
    void mode1();
    void mode2();
    void mode3();

protected:
    /* Functions */
    void initializeGL();
    void resizeGL(int x, int h);
    void paintGL();
    void createScene(void);

    QGLShader *m_vertexShader;
    QGLShader *m_fragmentShader;
    QGLShaderProgram *m_shaderProgram;

    QGLBuffer *m_vboVertices;
    QGLBuffer *m_vboColors;

    QVector3D* m_points;
    QVector3D* m_point_colours;

    QMatrix4x4 m_matrixTransformation;

private:
    /* variables */
    int xrot , yrot, zrot, delay;
    qreal zoom;
    ParticleSimulator *sys;
    QTimer *timer;
};

#endif // OPENGL_H
