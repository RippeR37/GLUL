#!/bin/bash


echo "###############################"
echo "### Installing dependencies ###"
echo "###############################"


SET DEPENDENCY_GLM_BRANCH="0.9.5"
SET DEPENDENCY_GLEW_VERSION="1.13.0"
SET DEPENDENCY_FT2_VERSION="2.6"
SET DEPENDENCY_FT2_VERSION_FILE="26"


echo "Configuring directories..."
    cd ../../
    mkdir external
    cd external
echo "Done."


echo "Installing GLM..."
    git clone -b $DEPENDENCY_GLM_BRANCH --depth 1 https://github.com/g-truc/glm.git glm
    cd glm
    cmake .
    make install
    cd ..
echo "Done."


echo "Installing GLEW..."
    wget -O glew-${DEPENDENCY_GLEW_VERSION}.zip https://sourceforge.net/projects/glew/files/glew/${DEPENDENCY_GLEW_VERSION}/glew-${DEPENDENCY_GLEW_VERSION}.zip/download
    unzip glew-${DEPENDENCY_GLEW_VERSION}.zip
    cd glew-${DEPENDENCY_GLEW_VERSION}
    make
    make install
    cd ..
echo "Done."


echo "Installing GLFW..."
    git clone -q --depth 1 https://github.com/glfw/glfw.git glfw
    cd glfw
    cmake -DBUILD_SHARED_LIBS=ON
    make install
    cd ..
echo "Done."


echo "Installing FreeType2..."
    wget -O ft${DEPENDENCY_FT2_VERSION_FILE}.zip http://sourceforge.net/projects/freetype/files/freetype2/${DEPENDENCY_FT2_VERSION}/ft${DEPENDENCY_FT2_VERSION_FILE}.zip/download
    unzip ft${DEPENDENCY_FT2_VERSION_FILE}.zip
    cd freetype-${DEPENDENCY_FT2_VERSION}
    cmake .
    make install
    cd ..
echo "Done."


echo "Ending instalation..."
    cd ..
echo "Done."
