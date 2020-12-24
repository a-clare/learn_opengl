# Learn OpenGL

My implementations of the tutorials https://learnopengl.com/Introduction.

I developed on a Mac so the code supplied with the tutorials did not work/compile. I also wanted to do it my self to get a better understanding. 
As such these will not be a word for word copy of the original implementations and may not be complete.

## VIS 

I created a library `vis` that all the tutorials, and examples will link against. This is where code common across all tutorials will be placed: opening windows, reading shaders, etc

## Submodules
`git clone git@github.com:AdamTheCanadian/learn_opengl.git`
`cd learn_opengl`
`git submodule update --recursive` 

**GLFW**
Used for managing windows and user input.

**GLAD**
I technically copied GLAD (not an actual git submodule) into the repo. So if it doesnt work try getting glad yourself from 
https://github.com/Dav1dde/glad