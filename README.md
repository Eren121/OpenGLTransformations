# OpenGL 2D transformations vizualizer

*To understand OpenGL transformations*

![Screenshot](https://raw.githubusercontent.com/Eren121/OpenGLTransformations/master/assets/screenshots/img.png)


Simple interactive vizualization of transformations for 2D shapes implemented
in pure OpenGL3, using SDL for image loading and FreeType for font rendering.

The functionalities are similar to the SFML library.
## Coordinates

Each cell of the grid represent one OpenGL unit.

Vertices position and translation are not the same! Results
will be different if there is scaling or rotation.

## Transformations

The transformations are the same as the SFML, except than this application use Y origin at bottom
while SFML origin is top. That mean rotation is counter-clockwise order, while the
SFML use clockwise rotation order.

## Outline

Supports outline color. I do not know if it is the exact same algorithm
as the SFML but the rendering is similar.

## Shapes

- Triangle
- Circle
- Text

## Dependencies

- **FreeType** (included)
- **sigslot** (included)
- **Dear IMGUI** (included)
- **SDL2** for window management (not included)
- **SDL2_image** for image loading and conversion (not included)

## Building

Make sure to clone this repository with submodules :

    git clone --recurse-submodules --remote-submodules https://github.com/Eren121/OpenGLTransformations.git

And standard CMake workflow :

    cd OpenGLTransformations
    mkdir build && cd build && cmake .. && cmake --build .
