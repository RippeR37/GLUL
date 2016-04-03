@echo OFF
setlocal


echo "###############################"
echo "### Installing dependencies ###"
echo "###############################"


echo "Configuring directories..."
    cd ../../
    mkdir libs
    cd libs
echo "Done."


echo "Installing GLM..."
    git clone -q -b 0.9.5 --depth 1 https://github.com/g-truc/glm.git glm-0.9.5.4/
    mkdir glm-0.9.5.4\include
    move glm-0.9.5.4\glm glm-0.9.5.4\include\glm > nul
echo "Done."


echo "Installing GLEW..."
    powershell -Command "& { (new-object System.Net.WebClient).DownloadFile('https://www.dropbox.com/s/psb96votnpm6ulw/glew-1.12.0.zip?dl=1', 'glew.zip'); }"
    7z x glew.zip > nul
echo "Done."


echo "Installing GLFW..."
    powershell -Command "& { (new-object System.Net.WebClient).DownloadFile('https://github.com/glfw/glfw/releases/download/3.1/glfw-3.1.bin.WIN32.zip', 'glfw.zip'); }"
    7z x glfw.zip > nul
    move glfw-3.1.bin.WIN32 glfw-3.1 > nul
echo "Done."


echo "Installing FreeType2..."
    powershell -Command "& { (new-object System.Net.WebClient).DownloadFile('https://www.dropbox.com/s/6kvjny8dgt0dkai/freetype-2.5.5.zip?dl=1', 'freetype2.zip'); }"
    7z x freetype2.zip > nul
echo "Done."


echo "Installing LIBJPEG..."
    powershell -Command "& { (new-object System.Net.WebClient).DownloadFile('https://www.dropbox.com/s/rtjlezqqqny3lr0/jpeg-9a.rar?dl=1', 'libjpeg.zip'); }"
    7z x libjpeg.zip > nul
echo "Done."


echo "Installing LIBPNG..."
    powershell -Command "& { (new-object System.Net.WebClient).DownloadFile('https://www.dropbox.com/s/5081ts8grc90xkj/libpng-1.6.17.rar?dl=1', 'libpng.zip'); }"
    7z x libpng.zip > nul
echo "Done."


echo "Installing ZLIB..."
    powershell -Command "& { (new-object System.Net.WebClient).DownloadFile('https://www.dropbox.com/s/857rpc08be1ya82/zlib-1.2.8.rar?dl=1', 'zlib.zip'); }"
    7z x zlib.zip > nul
echo "Done."


echo "Installing GTEST..."
    powershell -Command "& { (new-object System.Net.WebClient).DownloadFile('https://www.dropbox.com/s/z74oruxw6syaua8/gtest-1.7.0.rar?dl=1', 'gtest.zip'); }"
    7z x gtest.zip > nul
echo "Done."


echo "Ending instalation..."
    cd ..
echo "Done."
