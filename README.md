# MyShootingTownProject — OpenGL 3.3, GLFW, GLAD, GLM

A small first‑person “town” rendered with modern OpenGL. It uses:

- GLFW for windowing and input
- GLAD for OpenGL function loading (bundled in `src/glad.c`)
- GLM for math (vectors/matrices)

You can walk around with WASD + mouse, explore houses/trees/targets placed randomly on a ground plane, and the camera has simple collision so you don’t walk through objects.

## Controls

- W/A/S/D: move
- Mouse: look around
- ESC: quit

## Build: prerequisites by platform

You need a C/C++ toolchain, GLFW, and GLM.

Before running the `make` install glm and glfw packages in your system

## Build and run

From the project root:

```bash
make            # builds the project using detected platform settings
./hw3           # runs the assignment
```

## Time Spent

Approximate total time spent: ~4 Days (coding + testing + documentation).

## Why Using GLM GLFW GLAD?

GLFW (windowing + input)

Why: Lightweight, focused on creating OpenGL contexts and handling keyboard/mouse. Cross‑platform and very common in modern OpenGL tutorials. Plays nicely with raw OpenGL and simple Makefiles.
Why not others:
GLUT/FreeGLUT: Old and limited; Apple’s GLUT is deprecated, and core-profile support/input handling is weaker.

GLAD (OpenGL function loader)

Why: Modern, easy to generate/load OpenGL 3.3+ core functions. Works well on macOS core profile. We’ve bundled it, so no extra install steps.
Why not others:
GLEW: Works, but can be fussier with core profile on macOS and is a bit older in design.
Rolling our own loader: Platform-specific, tedious, and error‑prone.

GLM (math: vec/mat/quats)

Why: Header‑only, zero runtime dependency, and mirrors GLSL types and functions (vec3, mat4, normalize, lookAt), so shader math translates directly to C++. Very standard in OpenGL projects.
Why not others:
Eigen/Armadillo: Powerful linear algebra libs but heavier and not GLSL‑style; more than we need.
Hand‑written math: Reinventing wheels and easy to get wrong; GLM is tested and idiomatic for OpenGL.
