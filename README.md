# This project was made to show how is working ps1 Render piplyne.

Ps1 model model drawing is not same like standart 3D work. Ps1's GPU could draw only 300000 polygons. This is very important.

For run my render you need do this command:
```bash
#go to glm folder and install glm library
cd include/glm
#next intall glm source code
git clone https://github.com/g-truc/glm
#next leave include directory and make folder build
mkdir build
cd build
cmake ..
cmake --build .
#next go to folder debug and run file
cd debug
./ps1render
