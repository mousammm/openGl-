# align the top and left 
    const std::vector<GLfloat> vertexData {
        // x     y      z
        -0.5f,  0.5f, 0.0f,   //vertex 1 (top)
    };

# winding order are dirr ouur vertices are laid out (Left ver -> right vert -> top vert )

# modify for quad 
    const std::vector<GLfloat> vertexData {
        // x     y      z
        -0.5f, -0.5f, 0.0f,  //vertex 1  ( bot left )
         1.0f,  0.0f, 0.0f, //color v1
			      
         0.5f, -0.5f, 0.0f,  //vertex 1  (bot right )
         0.0f,  1.0f, 0.0f,  //color v2
			      
        -0.5f,  0.5f, 0.0f,   //vertex 1 (top left )
         0.0f,  0.0f, 1.0f,    // color v3
        //
        // second triangle 
         0.5f, -0.5f, 0.0f,  //vertex 1  (bot right )
         0.0f,  1.0f, 0.0f,    // color v3
	
         0.5f,  0.5f, 0.0f,   //vertex 1 (top right )
         1.0f,  0.0f, 0.0f, //color v1
 
        -0.5f,  0.5f, 0.0f,  //vertex 1  (top left )
         0.0f,  0.0f, 1.0f,  //color v2
    };

# modify for 6 vertices 
    glDrawArrays(GL_TRIANGLES, 0, 6);
