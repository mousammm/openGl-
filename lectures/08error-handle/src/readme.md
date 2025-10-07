# added this 
// error handle
static void glClearAllErrorHandle(){
    while (glGetError() != GL_NO_ERROR ) {
    }
}

// return true if we have an error 
static bool GlCheckErrorStatus(const char* function, int line){
    while (GLenum error = glGetError()) {
        std::cout << "OpenGl error:" << error 
                  << "\t Line: " << line 
                  << "\t Function: " << function
                  << std::endl;
        return true;
    }
    return false;
}

#define GlCheck(x) glClearAllErrorHandle(); x; GlCheckErrorStatus(#x, __LINE__ );
// error handle end


# to use 
GlCheck(fun();)
