#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>

// globals 
int gWidth = 640;
int gHeight = 480;
SDL_Window* gWindow = nullptr;
SDL_GLContext gOpenGlContext = nullptr;

bool gQuit = false; // true = stop running

void getOglDetatils();
void initProg();
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

}
void draw(){
}


void cleanUp(){
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}


