#include <GL/glut.h>
#include <stdio.h>

#ifndef FL_COLOR
#define FL_COLOR(x) ((float)(x)/255.0f)
#endif

GLfloat angle=0.0;
GLfloat pos=0.0;
void spin(void)
{
    printf("spin()\n");
//    angle+=1.0;
    pos+=0.01;
    glutPostRedisplay();
}

void display(void)
{
    printf("display()\n"); //d
    glClearColor(FL_COLOR(209),FL_COLOR(206),FL_COLOR(192),0.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

//    glScalef(0.5f, 1.0f, 2.0f); //works
//    glutWireCube(2.0);

    glColor3f(0.2,0.5,0.8);

    glRectf(0.005f,-0.5f,0.03f,0.9f);
    glRectf(0.035f,-0.5f,0.06f,0.9f);

//    glRectf(0.0f,0.0f,1.0f,-1.0f); //d

    glutSwapBuffers();
// glFlush(); //redundant
}

void keyboard(unsigned char key, int x, int y)
{
    printf("keyboard()\n");//d
    if (key == 27)
	exit (0); /* 27 is the Escape key */
    else
	printf ("You pressed %c\n", key);
}

void reshape(int w, int h)
{
    printf("reshape()\n"); //d
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    //gluPerspective(60, (GLfloat)w/(GLfloat)h,1.0,100.0);
    glOrtho(-1.0,1.0, -1.0,1.0, -1.0,1.0);
    glMatrixMode (GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(600,400);
    glutInitWindowPosition(100,100);
    glutCreateWindow ("sort visualisation");
    glutDisplayFunc (display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc (keyboard);
    //glutIdleFunc(spin);
    glutMainLoop ();
    return 0;
}
