#include "opengl.h"

OpenGL::OpenGL(QWidget *parent) :
    QGLWidget(parent)
{
}

void OpenGL::initializeGL(){
    glClearColor(0,0,0,0);
    glClearDepth(1);

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

    createScene();
}

void OpenGL::createScene(){
    int num_vertices = 8;
    QVector3D *vertices = new QVector3D[num_vertices*2]; // *2 to allocate space for colors

    for (int i = 0; i< num_vertices; i++)
        vertices[i] = QVector3D(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX);

    // each vertex has a random RGB color
    for(int i=0; i<num_vertices; i++)
    {
        // append to buffer of vertices
        vertices[i+num_vertices] = QVector3D(1,1,1);/*rand()/(float)RAND_MAX,
                                             rand()/(float)RAND_MAX,
                                             rand()/(float)RAND_MAX);*/
    }

    // create indices to array of vertices
    int num_indices = 24;
    GLubyte *indices = new GLubyte[num_indices];
    indices[ 0] = 0; indices[ 1] = 1; indices[ 2] = 2; indices[ 3] = 3; // front
    indices[ 4] = 7; indices[ 5] = 6; indices[ 6] = 5; indices[ 7] = 4; // back
    indices[ 8] = 1; indices[ 9] = 5; indices[10] = 6; indices[11] = 2; // top
    indices[12] = 0; indices[13] = 3; indices[14] = 7; indices[15] = 4; // bottom
    indices[16] = 1; indices[17] = 0; indices[18] = 4; indices[19] = 5; // left
    indices[20] = 3; indices[21] = 2; indices[22] = 6; indices[23] = 7; // right

    // create VBO for vertices
    m_vboVertices = new QGLBuffer(QGLBuffer::VertexBuffer);
    m_vboVertices->create();
    m_vboVertices->bind();
    m_vboVertices->setUsagePattern(QGLBuffer::StaticDraw);
    m_vboVertices->allocate(vertices, num_vertices*2*sizeof(QVector3D));
    delete []vertices;

    // create VBO for indices
    m_vboIndices = new QGLBuffer(QGLBuffer::IndexBuffer);
    m_vboIndices->create();
    m_vboIndices->bind();
    m_vboIndices->setUsagePattern(QGLBuffer::StaticDraw);
    m_vboIndices->allocate(indices, num_indices*sizeof(GLubyte));
    delete []indices;
}

void OpenGL::resizeGL(int x, int h){
    glViewport(0, 0, (GLuint) x, (GLuint) h);
}

void OpenGL::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // bind VBOs for vertex array and index array
    m_vboVertices->bind();
    m_vboIndices->bind();

    m_shaderProgram->enableAttributeArray("vPosition"); // or m_shaderProgram->enableAttributeArray(0)
    m_shaderProgram->enableAttributeArray("vColor"); // or m_shaderProgram->enableAttributeArray(1)

    m_shaderProgram->setAttributeBuffer("vPosition", GL_FLOAT, 0, 3, 0);
    m_shaderProgram->setAttributeBuffer("vColor", GL_FLOAT, 8*sizeof(QVector3D), 3, 0);
    glDrawElements(GL_POINTS, 24, GL_UNSIGNED_BYTE, 0);

    m_shaderProgram->disableAttributeArray("vPosition");
    m_shaderProgram->disableAttributeArray("vColor");

    // switch back to non-VBO pointer operation
    m_vboVertices->release();
    m_vboIndices->release();

    m_matrixTransformation.setToIdentity();
    m_shaderProgram->setUniformValue("MatrixTransformation", m_matrixTransformation);

    glBegin(GL_LINES);
      glColor3f(1,0,0);
      glVertex2f(0,-10);
      glVertex2f(0,10);
    glEnd();

    glBegin(GL_LINES);
      glColor3f(0,1,0);
      glVertex2f(-10,0);
      glVertex2f(10,0);
    glEnd();

}

void OpenGL::xslot(int n){
    xrot = n;
    m_matrixTransformation.rotate(xrot,1,0,0);
    m_matrixTransformation.rotate(yrot,0,1,0);
    m_matrixTransformation.rotate(zrot,0,0,1);
    m_shaderProgram->setUniformValue("MatrixTransformation", m_matrixTransformation);
    updateGL();
}

void OpenGL::yslot(int n){
    yrot = n;
    m_matrixTransformation.rotate(xrot,1,0,0);
    m_matrixTransformation.rotate(yrot,0,1,0);
    m_matrixTransformation.rotate(zrot,0,0,1);
    m_shaderProgram->setUniformValue("MatrixTransformation", m_matrixTransformation);
    updateGL();
}

void OpenGL::zslot(int n){
    zrot = n;
    m_matrixTransformation.rotate(xrot,1,0,0);
    m_matrixTransformation.rotate(yrot,0,1,0);
    m_matrixTransformation.rotate(zrot,0,0,1);
    m_shaderProgram->setUniformValue("MatrixTransformation", m_matrixTransformation);
    updateGL();
}
