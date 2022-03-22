# Sybil-Engine

## 3rd-Party Libraries (included as git modules and may not be the complete list)
GLFW
GLAD
GLM
ImGUI
cmake
stb_image
freetype

Thinking About:
OpenAL-Soft (maybe even just OpenAL if I feel like learning audio)
JSON Parser for C++ (maybe nlohmann/json)

## References
Framework portion took heavy inspiration from SFML and XNA/Monogame.
Portions of the OpenGL wrappers were referenced from Cherno's OpenGL series on youtube: https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2 aswell as from learnopengl.com


## Structure
Planning on 3 major layers:

1. Framework: Consists of graphics, window, input, and audio api.  
2. Engine: essentially just the Entity-Component System coupled with a Renderer
3. Editor: ImGUI tools to make the game (I don't think I'll go beyond native scripting though)

The Editor should essentially just be a game written with the Engine. The games created will be a layer on top of the Engine like the editor. They should not be on top the of the editor.