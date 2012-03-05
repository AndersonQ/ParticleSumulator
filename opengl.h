#ifndef OPENGL_H
#define OPENGL_H

#include <QGLWidget>

#include <QGLShader>
#include <QGLShaderProgram>
#include <QGLBuffer>
#include <QMatrix4x4>
#include <QVector3D>

class OpenGL : public QGLWidget
{
    Q_OBJECT
public:
    explicit OpenGL(QWidget *parent = 0);

signals:

public slots:
    void xslot(int n);
    void yslot(int n);
    void zslot(int n);
    void zoomslot(int n);

protected:
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
    QVector3D* m_point_colors;

    QMatrix4x4 m_matrixTransformation;

private:
    int xrot , yrot, zrot, zoom;
    unsigned int MAX_NUM_PARTICLES;
};

#endif // OPENGL_H
