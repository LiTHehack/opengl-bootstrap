// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#ifndef __APPLE__
#include <GL/glew.h>
#endif

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <iostream>
#include "common/Shader.h"

using namespace glm;
void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}
        glfwSetErrorCallback(error_callback);

        
        glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


        const GLchar *vertex_shader[] = {
          "#version 400 core\n",
          "in vec3 inputColor;\n",
          "in vec4 inputPosition;\n",
          "out vec3 color;\n",
          "void main(void) {\n",
          "    color = inputColor;\n",
          "    gl_Position = inputPosition;\n",
          "}"
        };

        const GLchar *color_shader[] = {
          "#version 400 core\n",
          "in vec3 color;\n",
          "out vec4 finalColor;\n",
          "void main() {\n",
          "    finalColor = vec4(color,1.0);\n",
          "}"
        };
        
        //Open a window
        GLFWwindow* window = glfwCreateWindow(640, 480, "This is a test", NULL, NULL);
        if(!window){
          fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
          glfwTerminate();
          return -1;
        }

        int major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
        int minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
        int rev = glfwGetWindowAttrib(window, GLFW_CONTEXT_REVISION);

        fprintf(stderr, "OpenGL version recieved: %d.%d.%d\n", major, minor, rev);
        // Ensure we can capture the escape key being pressed below
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE );
        glfwMakeContextCurrent(window);

	// Initialize GLEW if not on apple
        // Apple already has such context-info, and thus, this isn't needed.
        #ifndef __APPLE__        
        glewExperimental=GL_TRUE;
        GLenum err = glewInit();
        if (err != GLEW_OK) {
          fprintf(stderr, "Failed to initialize GLEW\n");
          fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
          return -1;
        }
        fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
        #endif

	// Dark blue background
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        static ShaderProgram prog(vertex_shader, color_shader);
        
	do{
          prog();

          float ratio;
          int width, height;
          glfwGetFramebufferSize(window, &width, &height);
          ratio = width / (float) height;
          glViewport(0, 0, width, height);
          glClear(GL_COLOR_BUFFER_BIT);


          glfwSwapBuffers(window);
          glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while( !glfwWindowShouldClose(window));

	// Close OpenGL window and terminate GLFW
        glfwDestroyWindow(window);
	glfwTerminate();
        exit(EXIT_SUCCESS);
}
