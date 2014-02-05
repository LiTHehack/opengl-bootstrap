#OpenGL Bootstrap
In order to clone, compile and run this:

    git clone --recursive https://github.com/kallekrantz/opengl-bootstrap.git
    cd opengl-bootstrap/build
    cmake ..
    make -j4
    ./Opengl-Bootstrap


If you want to add tests, add these under test directory, these should have the suffix .cpp. The tests are run with Gtest, and for information on how to write these tests, check the documentation of Gtest.

If you want to run these tests, use the following commands

    cd build
    cmake ..
    make -j4
    ./Opengl-Bootstrap_test
    
This project __requires__ cmake, git and svn

To change the projects name (and the corresponding execuatables), change the ````set(PROJECT_NAME_STR Opengl-Bootstrap)```` line.

