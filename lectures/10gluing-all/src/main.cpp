#include <SDL2/SDL.h>  // for windowing and others inputs 
#include <glad/glad.h> // includes the opengl fun 

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// globals 
int gWidth = 640;
int gHeight = 480;
// int gWidth = 1920;
// int gHeight = 1080;
SDL_Window* gWindow = nullptr;
SDL_GLContext gOpenGlContext = nullptr;
bool gQuit = false; // true = stop running

GLuint gVAO  = 0; // VAO
GLuint gVBO  = 0; // VBO pos
// used to store the array of indices that we want to draw from 
// when we do index drawing 
GLuint gIBO  = 0; // Index buffer object
GLuint gGraphicPiplineShaderProgram = 0; // prg object for our shaderr

float g_Offset = 0.0f; // for shader 

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

// Function Declaration
std::string loadShaderAsString(const std::string& filename);
void initProg();

void vertexSpecification(); // get vertex data to gpu
void createGraphicPipeline(); // creating a pipeline with a vertex and fraggment shader
   GLuint createShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
       GLuint compileShader(GLuint type, const std::string& source);
 
void mainLoop();
   void preDraw();
   void input();
   void draw();
void cleanUp();
// funb dec edn 

std::string loadShaderAsString(const std::string& filename){
	// resultinng shader programm as a single program 
    std::string result = "";
    std::string line = "";
        
    std::ifstream myFile(filename.c_str());
    if (myFile.is_open()) {
        while (std::getline(myFile, line)) {
            result += line + "\n";
        }
        myFile.close();
    }
    return result;
}

int main(int argc, char* argv[]){

    std::cout << "hello wrld"<< std::endl;

    // 1.setup the sdl and graphic enngine 
    initProg(); 

    // 2.setup the the vertecies on to the cpu transfering those to gpu 
    vertexSpecification();

    // 3. useful for setting up the vertex and fragment shader 
    createGraphicPipeline();

    // 4.use the graphic pipline to draw the triangle
    mainLoop();

    cleanUp();

    return 0;
}

void initProg(){
    // initialize sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        std::cout << "SDL2 cannot initialize"<< std::endl;
        exit(1);
    }

    // set up opengl context use < 4.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // depricated function remove
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // for smooth updating 
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // create a window using sdl that support sdl
    gWindow = SDL_CreateWindow("opengl window",0,0,gWidth,gHeight,SDL_WINDOW_OPENGL);
    if (gWindow == nullptr) {
        std::cout << "SDL2 cannot create window"<< std::endl;
        exit(1);
    }

    // create an opengl graphics context (big object that encapsulate everything)
    gOpenGlContext = SDL_GL_CreateContext(gWindow);
     if ( gOpenGlContext == nullptr) {
        std::cout << "Opengl context cannot be created "<< std::endl;
        exit(1);
    }

    // init glad  bring all the opengl fun 
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cout << "Glad was not initialise"<< std::endl;
        exit(1);
    }

}

// setting up our geometry data 
// here we store z,y,x pos attribute within vertex position for the data 
// for now this data is stored in cpu shortly we are going to store in the gpu in a call to the glBuferData which will store this info into a vertex buffer object 
void vertexSpecification(){
    // lives on the cpu 
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


    // sending things up on GPU
    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);

    // start generating our VBO
    glGenBuffers(1,&gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER,
                 vertexData.size() * sizeof(GLfloat),
                 vertexData.data(),
                 GL_STATIC_DRAW);

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

    // linkng up our pos in vao pos info
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,
                          sizeof(GL_FLOAT)*6,(void*)0);

   
    // linkng up our color in vao color info
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,
                          sizeof(GL_FLOAT)*6,(GLvoid*)(sizeof(GL_FLOAT)*3)
                          );

    // cleanup 
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
} 

void createGraphicPipeline(){
    std::string vertexShaderSource = loadShaderAsString("./shader/vert.glsl");
    std::string fragmentShaderSource = loadShaderAsString("./shader/frag.glsl");

    // ADD THESE CHECKS:
    if (vertexShaderSource.empty()) {
        std::cerr << "ERROR: Vertex shader source is empty!" << std::endl;
        return;
    }
    if (fragmentShaderSource.empty()) {
        std::cerr << "ERROR: Fragment shader source is empty!" << std::endl;
        return;
    }

    std::cout << "Vertex shader loaded, size: " << vertexShaderSource.size() << std::endl;
    std::cout << "Fragment shader loaded, size: " << fragmentShaderSource.size() << std::endl;

    gGraphicPiplineShaderProgram = createShaderProgram(vertexShaderSource,fragmentShaderSource);
} 

GLuint createShaderProgram(const std::string& vertexShaderSource, 
                           const std::string& fragmentShaderSource){
    GLuint programObject = glCreateProgram();

    GLuint myVertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint myFragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(programObject, myVertexShader);
    glAttachShader(programObject, myFragmentShader);
    glLinkProgram(programObject);

    // validate our programm 
    glValidateProgram(programObject);
    // glDetach, glDeleteShader 
    // Clean up shaders after linking
    glDeleteShader(myVertexShader);
    glDeleteShader(myFragmentShader);


    return programObject;
}

GLuint compileShader(GLuint type, const std::string& source){
    GLuint shaderObject;

    if (type == GL_VERTEX_SHADER) {
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
        
    }else if (type == GL_FRAGMENT_SHADER) {
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    }

    const char* src = source.c_str();
    glShaderSource(shaderObject,1, &src, nullptr );
    glCompileShader(shaderObject);

     // shder log start 
     int result;
     glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);
    
     if(result == GL_FALSE){
           int length;
           glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &length);
           char* errorMessage = new char[length];
           glGetShaderInfoLog(shaderObject, length, &length, errorMessage);
    
           if(type == GL_VERTEX_SHADER){
      	    std::cout<< "Error GL_VERTEX_SHADER compilation failed!\n"<<errorMessage<<std::endl;
             }else if(type == GL_FRAGMENT_SHADER){
      	    std::cout<< "Error GL_FRAGMENT_SHADER compilation failed!\n"<<errorMessage<<std::endl;
             }
           // reclaim our memory 
           delete[] errorMessage;
    
           // delete our broken shadder
           glDeleteShader(shaderObject);
    
           return 0;
    
     } // glsl log end

    return shaderObject;
}

void mainLoop(){

    while (!gQuit) {
        input();
        preDraw();
        draw();
        
        SDL_GL_SwapWindow(gWindow); // update the screen
    }

}

void input(){
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
            case SDL_QUIT:
                std::cout << "SDL2 QUIT"<< std::endl;
                gQuit = true;

            case SDL_KEYUP:
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                         std::cout << "SDL2 QUIT"<< std::endl;
                         gQuit = true;
              } // keyyup end
            default:
                
                break;
        } // while end
        
    } // poll end

    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_W]) {
        std::cout << "g_Offset"<< g_Offset << std::endl;
        g_Offset += 0.01;
     }
    if (keystate[SDL_SCANCODE_D]) {
    }
    if (keystate[SDL_SCANCODE_S]) {
        std::cout << "g_Offset"<< g_Offset << std::endl;
        g_Offset -= 0.01;
     }
    if (keystate[SDL_SCANCODE_A]) {
    }

    
}
void preDraw(){
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0,0,gWidth,gHeight);
    glClearColor(0.f, 0.f, 0.f, 1.f); // bg black 

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

    glUseProgram(gGraphicPiplineShaderProgram);

    GLint location = glGetUniformLocation( gGraphicPiplineShaderProgram, "u_Offset");
    if (location >= 0) {
        glUniform1f(location,g_Offset);
    }


}
void draw(){
    // enble our atribute 
    glBindVertexArray(gVAO);

    // select the vertex buffer object we want to enable 
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);

    // render data
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, 0);

    // not neccessary is on egraphic pipline  
    glUseProgram(0);
}


void cleanUp(){
   SDL_GL_DeleteContext(gOpenGlContext);

   SDL_DestroyWindow(gWindow);
    SDL_Quit();
}


