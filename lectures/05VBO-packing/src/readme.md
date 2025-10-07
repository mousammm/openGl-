# packing 2 VBO in 1 
so we dont have to manage 2 VBO for pos and color 

# pack positon and color VBO  in one 
    const std::vector<GLfloat> vertexPosition {
        // x     y      z
        -0.8f, -0.8f, 0.0f,  //vertex 1
         1.0f,  0.8f, 0.055f, //color v1
			      
         0.8f, -0.8f, 0.0f,  //vertex 1
         0.0f,  1.0f, 0.02f,  //color v2
			      
         0.0f,  0.8f, 0.0f   //vertex 1
         0.0f,  1.0f, 1.0f    // color v3
    };

# delete // color 
    // color vbo2 
    glGenBuffers(1,&gVBO2);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO2);
    glBufferData(GL_ARRAY_BUFFER,
                 vertexColor.size() * sizeof(GLfloat),
                 vertexColor.data(),
                 GL_STATIC_DRAW);
 

 delete global ->  GLuint gVBO2  = 0; // VBO color
 renamme       ->  const std::vector<GLfloat> vertexData {
 change hopping ->     glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,
                          sizeof(GL_FLOAT) * 6,(void*)0);
  and this also 

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,
                          sizeof(GL_FLOAT)*6,(GLvoid*)(sizeof(GL_FLOAT)*3)
                          );



    // we need to set the ofset because we are not starting at 0 but 3

# now if we need to add a new ele in vbo we need to 
* 1st update  our stdide    stride = 6 (form x0 to x6)   ofsett 3 xyz and rgb
    vbo1 = {
   x,y,z, r,g,b
   x,y,z, r,g,b
   x,y,z, r,g,b
} 
