# OpenGL Bootstrap

This should install and run a simple OpenGL program with GLFW, GLEW, GLM and GTest.

## Getting started
In order to clone, compile and run this:

    git clone --recursive https://github.com/LiTHehack/opengl-bootstrap.git
    cd opengl-bootstrap/build
    cmake ..
    make -j4
    ./Opengl-Bootstrap

This should install everything, compile, link and run the example program.
    
#### Support

Macs and Linux is currently supported (Mac users need to change the OpengGL version in the [Opengl-Bootstrap file](src/opengl-bootstrap.cpp)). 
Windows support is currently very iffy. __Pull requests are welcome__.

### Requirements

This project __requires__ [CMake](http://www.cmake.org/download/), [Git](http://git-scm.com/) and [svn](https://subversion.apache.org/).

### Setup

To change the projects name (and the corresponding execuatables), change the ````set(PROJECT_NAME_STR Opengl-Bootstrap)```` line in [`CMakeLists.txt`](CMakeLists.txt).

## Tests

If you want to add tests, add these under test directory, these should have the suffix .cpp. The tests are run with [Gtest](https://code.google.com/p/googletest/), and for information on how to write these tests, check the documentation of Gtest.

If you want to run these tests, use the following commands

    cd build
    cmake ..
    make -j4
    ./Opengl-Bootstrap_test
