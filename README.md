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


## Structure

1. Framework: Consists of graphics, window, input, and audio api.  
2. Engine: essentially just the Entity-Component System coupled with a Renderer
3. Editor: ImGUI tools to make the game (I don't think I'll go beyond native scripting though)

The Editor should essentially just be a game written with the Engine. The games created will be a layer on top of the Engine like the editor. They should not be on top the of the editor.
