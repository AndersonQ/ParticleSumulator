#include "opengl.h"
#include "particle.h"
#include "particlesimulator.h"

OpenGL::OpenGL(QWidget *parent) :
    QGLWidget(parent)
{
    m_points = NULL;
    m_point_colours = NULL;

    m_vboVertices = NULL;
    m_vboColors   = NULL;

    /* Define the initial number of particles */
    sys = new ParticleSimulator(1000);
}

void OpenGL::initializeGL(){
    glEnable(GL_DEPTH_TEST);

    /* Set a random initial position and colour of particles */
    unsigned int p = sys->get_num_particles();
    for (unsigned int i = 0; i < p; i++){
        if (i%8 == 0)
            sys->par[i].SetPosition(QVector3D(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX));
        else if(i%8 == 1)
            sys->par[i].SetPosition(QVector3D(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX)*
                                    QVector3D(1,1,-1));
        else if(i%8 == 2)
                sys->par[i].SetPosition(QVector3D(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX)*
                                        QVector3D(1,-1,1));
        else if(i%8 == 3)
                sys->par[i].SetPosition(QVector3D(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX)*
                                        QVector3D(1,-1,-1));
        else if(i%8 == 4)
                sys->par[i].SetPosition(QVector3D(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX)*
                                        QVector3D(-1,1,1));
        else if(i%8 == 5)
                sys->par[i].SetPosition(QVector3D(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX)*
                                        QVector3D(-1,1,-1));
        else if(i%8 == 6)
                sys->par[i].SetPosition(QVector3D(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX)*
                                        QVector3D(-1,-1,1));
        else if(i%8 == 7)
                sys->par[i].SetPosition(QVector3D(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX)*
                                        QVector3D(-1,-1,-1));

        sys->par[i].SetColour(QVector3D(1,1,1));//(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX));
    }

    m_vertexShader = new QGLShader(QGLShader::Vertex);
    m_fragmentShader = new QGLShader(QGLShader::Fragment);

    if(!m_vertexShader->compileSourceFile(":/vshader.glsl"))
         qWarning() << m_vertexShader->log();

     if(!m_fragmentShader->compileSourceFile(":/fshader.glsl"))
         qWarning() << m_fragmentShader->log();

     m_shaderProgram = new QGLShaderProgram;
     m_shaderProgram->addShader(m_vertexShader);
     m_shaderProgram->addShader(m_fragmentShader);

     if(!m_shaderProgram->link())
         qWarning() << m_shaderProgram->log() << endl;
     else
         m_shaderProgram->bind();

     /* Define initial zoom */
     zoom = 1;

     createScene();
}

void OpenGL::createScene(){

    if (m_points!= NULL) delete []m_points;
    if (m_point_colours!=NULL) delete []m_point_colours;

    m_points = new QVector3D[sys->get_num_particles()];
    m_point_colours = new QVector3D[sys->get_num_particles()];

    /*   */
    for(unsigned int i = 0; i < sys->get_num_particles(); i++){
        m_points[i] = sys->par[i].Get_Position();
        m_point_colours[i] = sys->par[i].Get_Colour();
    }

    glPointSize(2.0);
    glClearColor(0.5, 0.5, 0.5, 1.0);

    // create VBO for vertices
    if (m_vboVertices != NULL)
    {
        m_vboVertices->release();
        m_vboVertices->destroy();
    }

    m_vboVertices = new QGLBuffer(QGLBuffer::VertexBuffer);
    m_vboVertices->create();
    m_vboVertices->bind();
    m_vboVertices->setUsagePattern(QGLBuffer::DynamicDraw);
    m_vboVertices->allocate(m_points, (sys->get_num_particles())*sizeof(QVector3D));
    delete []m_points;
    m_points = NULL;

    // create VBO for colors
    if (m_vboColors != NULL)
    {
        m_vboColors->release();
        m_vboColors->destroy();
    }

    m_vboColors = new QGLBuffer(QGLBuffer::VertexBuffer);
    m_vboColors->create();
    m_vboColors->bind();
    m_vboColors->setUsagePattern(QGLBuffer::DynamicDraw);
    m_vboColors->allocate(m_point_colours, (sys->get_num_particles())*sizeof(QVector3D));
    delete []m_point_colours;
    m_point_colours = NULL;
}

void OpenGL::resizeGL(int w, int h){
    /* adjust clipping box */

    QVector3D eye(1.5, 1.0, 1.0);
    QVector3D at(0.0, 0.0, 0.0);
    QVector3D up(0.0, 1.0, 0.0);
    QMatrix4x4 Projection, ModelView;
    Projection.setToIdentity();
    ModelView.setToIdentity();
    Projection.ortho(-2,2,-2,2,-4,4);

    ModelView.lookAt(eye,at,up);
    m_shaderProgram->setUniformValue("Projection", Projection);
    m_shaderProgram->setUniformValue("ModelView", ModelView);

    /* adjust viewport and  clear */

  /*  if(w<h) glViewport(0,0,w,w);
    else glViewport(0,0,h,h);

*/
    glViewport(0,0,w,h);
    /* set global size for use by drawing routine */
}

void OpenGL::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_vboVertices->bind();
    //pointer to GPU!!!
    /*QVector3D* pt = (QVector3D*) m_vboVertices->map(QGLBuffer::WriteOnly);
     for(unsigned int i=0; i < sys->get_num_particles(); i++)
     {
        pt[i] = m_points[i];
     }*/
     m_vboVertices->unmap();

    m_shaderProgram->enableAttributeArray("vPosition");
    m_shaderProgram->setAttributeBuffer("vPosition", GL_FLOAT, 0, 3, 0);


    m_vboColors->bind();
    /*QVector3D* pt_color = (QVector3D*) m_vboColors->map(QGLBuffer::WriteOnly);

    for(unsigned int i=0; i < sys->get_num_particles(); i++)
    {
       pt_color[i] = m_point_colours[i];
    }*/
    m_vboColors->unmap();

    m_shaderProgram->enableAttributeArray("vColor");
    m_shaderProgram->setAttributeBuffer("vColor", GL_FLOAT, 0, 3, 0);

    glDrawArrays(GL_POINTS, 0, sys->get_num_particles());

}

void OpenGL::xslot(int n){
    xrot = n;
    m_matrixTransformation.setToIdentity();
    m_matrixTransformation.rotate(xrot,1,0,0);
    m_matrixTransformation.rotate(yrot,0,1,0);
    m_matrixTransformation.rotate(zrot,0,0,1);
    m_matrixTransformation.scale(zoom,zoom,zoom);
    m_shaderProgram->setUniformValue("MatrixTransformation", m_matrixTransformation);
    updateGL();
}

void OpenGL::yslot(int n){
    yrot = n;
    m_matrixTransformation.setToIdentity();
    m_matrixTransformation.rotate(xrot,1,0,0);
    m_matrixTransformation.rotate(yrot,0,1,0);
    m_matrixTransformation.rotate(zrot,0,0,1);
    m_matrixTransformation.scale(zoom,zoom,zoom);
    m_shaderProgram->setUniformValue("MatrixTransformation", m_matrixTransformation);
    updateGL();
}

void OpenGL::zslot(int n){
    zrot = n;
    m_matrixTransformation.setToIdentity();
    m_matrixTransformation.rotate(xrot,1,0,0);
    m_matrixTransformation.rotate(yrot,0,1,0);
    m_matrixTransformation.rotate(zrot,0,0,1);
    m_matrixTransformation.scale(zoom,zoom,zoom);
    m_shaderProgram->setUniformValue("MatrixTransformation", m_matrixTransformation);
    updateGL();
}

void OpenGL::zoomslot(int n){
    zoom = 1 - (float) n / (float) 100;
    m_matrixTransformation.setToIdentity();
    m_matrixTransformation.rotate(xrot,1,0,0);
    m_matrixTransformation.rotate(yrot,0,1,0);
    m_matrixTransformation.rotate(zrot,0,0,1);
    m_matrixTransformation.scale(zoom,zoom,zoom);
    m_shaderProgram->setUniformValue("MatrixTransformation", m_matrixTransformation);
    updateGL();
}
