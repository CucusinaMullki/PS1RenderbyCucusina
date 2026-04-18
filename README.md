# This project was made to show how is working ps1 Render piplyne.

This program work with MSVC compiler

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
```
For upload your model you need in main write this:

1 import yout model in folder Asset
2 write this in main:
```cpp
//before loop !WORK ONLY WITH MODELS!
Object3D objname(ModelLoader::load("Path/to/your/model.obj", "Path/to/folder/where/yout/mtlfile.mtl", "Path/to/your/texture.png"), "name");

//for change position
objname.SetPosition({x, y, z});

//for change scale
objname.SetScale({x, y, z});

//for change rotation
objname.SetRotation(float pitch, float yaw, float roll);

//for move(forward/right/up) object
objname.MoveForward(float dist);
objname.MoveRight(float dist);
objname.MoveUp(float dist);

//for rotate object
objname.Rotate(float pitch, float yaw, float roll);

```
^
|
this can work with camera class and pointLight class

For draw your object you need use this in main loop:
``` cpp
objname.draw();

//after main loop
objname.deleteObject();
```