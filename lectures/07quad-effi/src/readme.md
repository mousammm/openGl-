# index buffering
we are currentyl using 2 triangle to display a quad (6 vertices)
but we need 4vertices to display 

# make a quad efficiiendty respecting the windiing direction 
    const std::vector<GLfloat> vertexData {
	 // 00 vertex
        -0.5f, -0.5f, 0.0f,  //vertex 1  ( bot left )
         1.0f,  0.0f, 0.0f, //color v1
			      
	 // 01 vertex
         0.5f, -0.5f, 0.0f,  //vertex 1  (bot right )
         0.0f,  1.0f, 0.0f,  //color v2
			      
	 // 02 vertex
        -0.5f,  0.5f, 0.0f,   //vertex 1 (top left )
         0.0f,  0.0f, 1.0f,    // color v3

	 // 03 vertex
         0.5f,  0.5f, 0.0f,   //vertex 1 (top right )
         1.0f,  0.0f, 0.0f, //color v1
    };


# added ondex buffer 
add this 

    const std::vector<GLuint> indexBufferData {2,0,1, 3,2,1 };
    // set up index buffer 
    glGenBuffers(1,&gIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
                 gIBO);
    // populate our index buffer 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indexBufferData.size()* sizeof(GLuint),
                 indexBufferData.data(),
                 GL_STATIC_DRAW
                 );

# for inndex drawing
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, 0);


