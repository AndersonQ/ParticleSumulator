#include "opengl.h"

OpenGL::OpenGL(QWidget *parent) :
    QGLWidget(parent)
{
    m_points = NULL;
    m_point_colors = NULL;

    m_vboVertices = NULL;
    m_vboColors   = NULL;
}

void OpenGL::initializeGL(){
    glEnable(GL_DEPTH_TEST);

    MAX_NUM_PARTICLES = 100;

    m_vertexShader = new QGLShader(QGLShader::Vertex);
    m_fragmentShader = new QGLShader(QGLShader::Fragment);

    if(!m_vertexShader->compileSourceFile("/media/Mokona/UFABC/10-Quad/Computacao.Grafica/Proj1/CG_Proj1/vshader.glsl"))
         qWarning() << m_vertexShader->log();

     if(!m_fragmentShader->compileSourceFile("/media/Mokona/UFABC/10-Quad/Computacao.Grafica/Proj1/CG_Proj1/fshader.glsl"))
         qWarning() << m_fragmentShader->log();

     m_shaderProgram = new QGLShaderProgram;
     m_shaderProgram->addShader(m_vertexShader);
     m_shaderProgram->addShader(m_fragmentShader);

     if(!m_shaderProgram->link())
         qWarning() << m_shaderProgram->log() << endl;
     else
         m_shaderProgram->bind();
     zoom = 1;
     createScene();
}

void OpenGL::createScene(){

    if (m_points!= NULL) delete []m_points;
    if (m_point_colors!=NULL) delete []m_point_colors;

    m_points = new QVector3D[MAX_NUM_PARTICLES];
    m_point_colors = new QVector3D[MAX_NUM_PARTICLES];

    /* initialize readom locations of particles */
    for(unsigned int i = 0; i < MAX_NUM_PARTICLES; i++)
        m_points[i] = QVector3D(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX);

    /* initialize random color for particles */
    for(unsigned int i = 0; i < MAX_NUM_PARTICLES; i++)
        m_point_colors[i] = QVector3D(1,1,1);

    glPointSize(5.0);
    glClearColor(0.5, 0.5, 0.5, 1.0);

    /* create VBO for vertices
    if (m_vboVertices != NULL)
    {
        m_vboVertices->release();
        m_vboVertices->destroy();
    }*/

    m_vboVertices = new QGLBuffer(QGLBuffer::VertexBuffer);
    m_vboVertices->create();
    m_vboVertices->bind();
    m_vboVertices->setUsagePattern(QGLBuffer::DynamicDraw);
    m_vboVertices->allocate(m_points, (MAX_NUM_PARTICLES)*sizeof(QVector3D));
    //delete []m_points;
    //m_points = NULL;

    /* create VBO for colors
    if (m_vboColors != NULL)
    {
        m_vboColors->release();
        m_vboColors->destroy();
    }*/

    m_vboColors = new QGLBuffer(QGLBuffer::VertexBuffer);
    m_vboColors->create();
    m_vboColors->bind();
    m_vboColors->setUsagePattern(QGLBuffer::DynamicDraw);
    m_vboColors->allocate(m_point_colors, (MAX_NUM_PARTICLES)*sizeof(QVector3D));
    //delete []m_point_colors;
    //m_point_colors = NULL;

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
    //m_matrixTransformation.setToIdentity();
    //m_shaderProgram->setUniformValue("MatrixTransformation", m_matrixTransformation);

    if (m_vboVertices == NULL){
        printf("NULLLLLLLLLLL!!!!!!!!!!!!\n");
        fflush(stdout);
    }
    m_vboVertices->bind();
    //pointer to GPU!!!
    QVector3D* pt = (QVector3D*) m_vboVertices->map(QGLBuffer::WriteOnly);
     for(unsigned int i=0; i < MAX_NUM_PARTICLES; i++)
     {
         printf("pt[%i] = m_points[%i]\n", i,i);
         if(m_points == NULL)
             puts("NULLLLLLLLLLLLLLLLLLLLLLL!");
         fflush(stdout);
        pt[i] = m_points[i];
     }
     m_vboVertices->unmap();

    m_shaderProgram->enableAttributeArray("vPosition");
    m_shaderProgram->setAttributeBuffer("vPosition", GL_FLOAT, 0, 3, 0);


    m_vboColors->bind();
    QVector3D* pt_color = (QVector3D*) m_vboColors->map(QGLBuffer::WriteOnly);

    for(unsigned int i=0; i < MAX_NUM_PARTICLES; i++)
    {
       pt_color[i] = m_point_colors[i];
    }
    m_vboColors->unmap();

    m_shaderProgram->enableAttributeArray("vColor");
    m_shaderProgram->setAttributeBuffer("vColor", GL_FLOAT, 0, 4, 0);

    glDrawArrays(GL_POINTS, 0, MAX_NUM_PARTICLES);

}

void OpenGL::xslot(int n){
    xrot = n;
    m_matrixTransformation.rotate(xrot,1,0,0);
    m_matrixTransformation.rotate(yrot,0,1,0);
    m_matrixTransformation.rotate(zrot,0,0,1);
    m_matrixTransformation.scale(zoom,zoom,zoom);
    m_shaderProgram->setUniformValue("MatrixTransformation", m_matrixTransformation);
    updateGL();
}

void OpenGL::yslot(int n){
    yrot = n;
    m_matrixTransformation.rotate(xrot,1,0,0);
    m_matrixTransformation.rotate(yrot,0,1,0);
    m_matrixTransformation.rotate(zrot,0,0,1);
    m_matrixTransformation.scale(zoom,zoom,zoom);
    m_shaderProgram->setUniformValue("MatrixTransformation", m_matrixTransformation);
    updateGL();
}

void OpenGL::zslot(int n){
    zrot = n;
    m_matrixTransformation.rotate(xrot,1,0,0);
    m_matrixTransformation.rotate(yrot,0,1,0);
    m_matrixTransformation.rotate(zrot,0,0,1);
    m_matrixTransformation.scale(zoom,zoom,zoom);
    m_shaderProgram->setUniformValue("MatrixTransformation", m_matrixTransformation);
    updateGL();
}

void OpenGL::zoomslot(int n){
    zoom = n;
    m_matrixTransformation.scale(zoom,zoom,zoom);
    m_shaderProgram->setUniformValue("MatrixTransformation", m_matrixTransformation);
    /*printf("scale %i\n", n);
    fflush(stdout);*/
    updateGL();
}
