#pragma once

#include <string>
#include <GLFW/glfw3.h>
namespace{
  void error_callback(int error, const char* description)
  {
    std::cerr << "Error code " << error << ": " << description << std::endl;
  }
}

class Init{
private:
  bool glewInitialized = false;
public:
  void glfw(int major, int minor){
    // Initialise GLFW
    if( !glfwInit() ){
      fprintf( stderr, "Failed to initialize GLFW\n" );
      exit(EXIT_FAILURE);
    }
    glfwSetErrorCallback(error_callback);

  
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  }
  
  void glew(){
    // Initialize GLEW if not on apple
    // Apple already has such context-info, and thus, this isn't needed.
#ifndef __APPLE__        
    if(glewInitialized){
      glewExperimental=GL_TRUE;
      GLenum err = glewInit();
      if (err != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
      }
      fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
      glewInitialized = true;
    }
#endif
  }

  GLFWwindow* window(int width = 640, int height = 480, std::string title = "Title", GLFWmonitor* monitor = NULL){
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), monitor, NULL);   
    if(!window){
      fprintf( stderr, "Failed to open GLFW window.\n" );
      glfwTerminate();
      exit(EXIT_FAILURE);
    }
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE );

    glew();
    return window;
  }

  void printWindowInfo(GLFWwindow* window){
    int major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    int minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
    int rev = glfwGetWindowAttrib(window, GLFW_CONTEXT_REVISION);

    fprintf(stderr, "Opened window has recieved OpenGL version: %d.%d.%d\n", major, minor, rev);
  } 
  
};

