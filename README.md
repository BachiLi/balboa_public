# balboa
UCSD CSE 167 codebase
https://cseweb.ucsd.edu/~tzli/cse167/

# Build
All the dependencies are included. Use CMake to build.
```
git clone --recurse-submodules https://github.com/BachiLi/balboa_public mkdir build
cd build
cmake ..
make -j
```
It requires compilers that support C++17 (gcc version >= 8, clang version >= 7, Apple Clang version >= 11.0, MSVC version >= 19.14).

For Windows users, directly loading CMakeLists.txt in your Visual Studio should work.

# Run
Try 
```
cd build
./balboa -hw 1_1
```
This will generate an image "hw1_1.png".

# Acknowledgement
stb\_image, stb\_image\_write, json, tinyply, GLFW, and glad

We use [stb_image](https://github.com/nothings/stb) and [stb_image_write](https://github.com/nothings/stb) for reading & writing images.

We use [json](https://github.com/nlohmann/json) to parse JSON files.

We use [tinyply](https://github.com/ddiakopoulos/tinyply) for parsing PLY files.

We use [glfw](https://www.glfw.org/) and [glad](https://glad.dav1d.de/) for the OpenGL homeworks.

3D models and textures: [Stanford 3D Scanning Repository](https://graphics.stanford.edu/data/3Dscanrep/), [KickAir_8p](https://blenderartists.org/t/uv-unwrapped-stanford-bunny-happy-spring-equinox/1101297), and [Texturemontage](http://kunzhou.net/tex-models.htm).
