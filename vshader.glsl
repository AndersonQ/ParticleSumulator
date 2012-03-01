attribute vec4 vPosition;
attribute vec4 vColor;
uniform mat4 MatrixTransformation;

varying vec4 color;

void main()
{
//    gl_Position = MatrixTransformation  * gl_Vertex;
//    gl_FrontColor = gl_Color;
    gl_Position = MatrixTransformation * vPosition;//gl_Vertex;
    color = vColor;
}
