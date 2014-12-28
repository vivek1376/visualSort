#include <GL/glut.h>
#include <stdio.h>

#ifndef FL_COLOR
#define FL_COLOR(x) ((float)(x)/255.0f)
#endif

#define BASELINE_Y -0.4f

GLfloat angle=0.0;
GLfloat pos=0.0;

void spin(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);
void createBars(int *, int num);

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
    int num[]={10,4,6,20,10,7,2,14,9,4,5,20,11,2,7,13,1,3,19,4};
    createBars(num,20);
//    glRectf(0.005f,BASELINE_Y,0.03f,0.9f);
    //  glRectf(0.035f,BASELINE_Y,0.06f,0.9f);

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

void createBars(int *values, int count)
{
    int i,max=0;
    float xOffset=((float)count*0.03f)/2.0f;

    /* find max value to find y scale length */
    for(i=0;i<count;i++)
	if(values[i]>max)
	    max=values[i];

    for(i=0;i<count;i++)
    {
	glRectf(i*0.03f-xOffset+0.005f,BASELINE_Y,(i+1)*0.03f-xOffset,((float)values[i]/max)*(0.9f-BASELINE_Y)+BASELINE_Y);	
    }
}
