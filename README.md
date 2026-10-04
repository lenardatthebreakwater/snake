# Snake

A Snake game written in C using the Raylib library.
The build instruction below is only for Windows since I don't use Linux. 

## Requirements
* GCC
* Raylib\
\
You can download both via the raylib installer from https://www.raylib.com/


## How to Build Project for Windows

* Clone this repo 

```bash
git clone https://github.com/lenardatthebreakwater/snake.git
```

* In the raylib installation directory, search for 'libraylib.a' and 'raylib.h.' Once found, copy and paste both files into the root directory of snake

* Within the same raylib installation directory, locate the 'w64devkit' folder. Ensure that you include the 'bin' path of this folder in your system's PATH

* Compiling to an Executable (make sure you are within snake first)

```bash
gcc -Wall -Wextra -o snake snake.c -I./ -L./ -lraylib -lopengl32 -lgdi32 -lwinmm
```  

