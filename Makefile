snake.exe: snake.c
	gcc -Wall -Wextra snake.c -o snake.exe -I./ -L./ -lraylib -lopengl32 -lgdi32 -lwinmm
