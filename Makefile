CC=gcc

qsVis: qsVis.c
	$(CC) -o qsVis qsVis.c -lglut -lGLU -lGL -lm -lGLEW

clean:
	rm -rf *o qsVis

