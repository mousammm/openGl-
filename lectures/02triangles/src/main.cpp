#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <vector>

// globals 
int gWidth = 640;
int gHeight = 480;
SDL_Window* gWindow = nullptr;
SDL_GLContext gOpenGlContext = nullptr;
bool gQuit = false; // true = stop running

GLuint gVAO  = 0; // VAO
GLuint gVBO  = 0; // VBO
GLuint gGraphicPiplineShaderProgram = 0; // prg object for our shaderr

// vertex shader 
const std::string gVertexShaderSource = 
    "#version 410 core\n"
    "in vec4 position;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(position.x,position.y,position.z,position.w);\n"
    "}\n";
// fragment shader 
const std::string gFragmentShaderSource = 
    "#version 410 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    " color = vec4(0.0f,0.5f,0.0f,1.0f);\n"
    "}\n";



// Function Declaration
void getOglDetatils();
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

void getOglDetatils(){
    std::cout << "Vendor: "<< glGetString(GL_VENDOR)<<std::endl;
    std::cout << "Renderer: "<< glGetString(GL_RENDERER)<<std::endl;
    std::cout << "Version: "<< glGetString(GL_VERSION)<<std::endl;
    std::cout << "Shading lang: "<< glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;
}

int main(){
    std::cout << "hello wrld"<< std::endl;
    initProg();

    vertexSpecification();
    createGraphicPipeline();

    mainLoop();
    cleanUp();
    return 0;
}

void initProg(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        std::cout << "SDL2 cannot initialize"<< std::endl;
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // depricated function remove
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    gWindow = SDL_CreateWindow("opengl window",0,0,gWidth,gHeight,SDL_WINDOW_OPENGL);
    if (gWindow == nullptr) {
        std::cout << "SDL2 cannot create window"<< std::endl;
        exit(1);
    }

    gOpenGlContext = SDL_GL_CreateContext(gWindow);
     if ( gOpenGlContext == nullptr) {
        std::cout << "SDL2 cannot create Opengl Context"<< std::endl;
        exit(1);
    }

    // init glad 
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cout << "Glad was not initialise"<< std::endl;
        exit(1);
    }

    getOglDetatils();
}

void vertexSpecification(){
    // lives on the cpu 
    const std::vector<GLfloat> vertexPosition {
        // x     y      z
        -0.8f, -0.8f, 0.0f,  //vertex 1
         0.8f, -0.8f, 0.0f,  //vertex 1
         0.0f,  0.8f, 0.0f   //vertex 1
    };

    // sending things up on GPU
    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);

    // start generating our VBO
    glGenBuffers(1,&gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER,
                 vertexPosition.size() * sizeof(GLfloat),
                 vertexPosition.data(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);

} 

void createGraphicPipeline(){
    gGraphicPiplineShaderProgram = createShaderProgram(gVertexShaderSource,gFragmentShaderSource);
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

    
}
void preDraw(){
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0,0,gWidth,gHeight);
    glClearColor(0.f, 0.f, 1.f, 1.f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

    glUseProgram(gGraphicPiplineShaderProgram);


}
void draw(){
    glBindVertexArray(gVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}


void cleanUp(){
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}


