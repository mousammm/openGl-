
vbo1 (0th postion) = position data
vbo2 (1th postion) = rgb data

# 1 in verspecificaton  added vertex color
void vertexSpecification(){
    const std::vector<GLfloat> vertexColor {
   };

# 2 add global 
GLuint gVBO2  = 0; // VBO color

# generate 2nd buff
    // color vbo2 
    glGenBuffers(1,&gVBO2);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO2);
    glBufferData(GL_ARRAY_BUFFER,
                 vertexColor.size() * sizeof(GLfloat),
                 vertexColor.data(),
                 GL_STATIC_DRAW);

    // linkng up our color in vao
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0);

    // disable
    glDisableVertexAttribArray(1);


# in fragment shader 
in vec3 v_vertexColors;

color = vec4(v_vertexColors.r, v_vertexColors.g, v_vertexColors.b, 1.0f);

# in vertex shader 
layout(location=0) in vec3 position;
layout(location=1) in vec3 vertexColors;

out vec3 v_vertexColors;

void main()
{
    v_vertexColors = vertexColors;
     gl_Position = vec4(position.x,position.y,position.z,1.0f);
};
