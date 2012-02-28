#ifndef OPENGL_H
#define OPENGL_H

#include <QGLWidget>

class OpenGL : public QGLWidget
{
    Q_OBJECT
public:
    explicit OpenGL(QWidget *parent = 0);

signals:

public slots:

protected:
    void initializeGL();
    void resizeGL(int x, int h);
    void paintGL();

};

#endif // OPENGL_H
