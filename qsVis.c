#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#ifndef FL_COLOR
#define FL_COLOR(x) ((float)(x)/255.0f)
#endif

#define BASELINE_Y -0.4f

GLfloat angle=0.0;
GLfloat pos=0.0;

int done=0;
int keyPress=0, pIndex=-1;
int pair[2];

//unsigned long int num[]={10,4,6,20,10,7,2,14,9,4,5,20,11,2,7,13,1,3,19,4};
unsigned long int *num,count;//[]={10,4,6,20,10,7,2,14,9,4,5,20,11,2,7,13,1,3,19,4};

void spin(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);
void createBars(unsigned long int *, int );
void idleFunc(void);

void quickSort (unsigned long int unsorted[], long int start, long int end_pos);
void genRandNos(void);
void printNos(void);

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
    glutIdleFunc(idleFunc);

    srand(time(NULL));
    genRandNos();

    display();
    quickSort(num,0,count-1);
    int i;
    for(i=0;i<20;i++)
	printf("%lu\n",num[i]);
//    getchar();
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

    glColor3f(FL_COLOR(16),FL_COLOR(148),FL_COLOR(148));
    
    createBars(num,count);
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
    {
//	done=1; /* 27 is the Escape key */
	exit(0);
//	printf("ESC pressed.\n");
    }
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

void createBars(unsigned long int *values, int count)//, int *pair)
{
    unsigned long int i,max=0;
    float xOffset=((float)count*0.03f)/2.0f;
//    float xOffset=((float)count*0.015f)/2.0f;
    /* find max value to find y scale length */

    for(i=0;i<count;i++)
	if(values[i]>max)
	    max=values[i];

    for(i=0;i<count;i++)
    {
	if (i==pair[0] || i==pair[1])
            glColor3f(FL_COLOR(150),FL_COLOR(81),FL_COLOR(81)); //red
	else
	    glColor3f(FL_COLOR(16),FL_COLOR(148),FL_COLOR(148));

	glRectf(i*0.03f-xOffset+0.005f,
		BASELINE_Y,
		(i+1)*0.03f-xOffset,
		((float)values[i]/max)*(0.9f-BASELINE_Y)+BASELINE_Y);	
/*	glRectf(i*0.015f-xOffset+0.002f,
		BASELINE_Y,
		(i+1)*0.015f-xOffset,
		((float)values[i]/max)*(0.9f-BASELINE_Y)+BASELINE_Y);	*/
    }
}

void quickSort (unsigned long int unsorted[], long int start, long int end)
{
    long int arr_len, i, j;
    unsigned long int pivot, temp, mid;
    arr_len = end - start + 1;

    keyPress=0;
    //    int pair[2];
    //    usleep(300000);

    //getchar();
    printf("-> ");
    printNos();

    //    display();

    /* base case */
    if (arr_len < 2)
        return;

    /* median pivot */
    
    mid = (start + end) / 2;
    
    if ( (unsorted[mid] >= unsorted[start] && unsorted[mid] <= unsorted[end]) ||
	 (unsorted[mid] <= unsorted[start] && unsorted[mid] >= unsorted[end]))
    {
	pIndex=mid;
	display();
	temp = unsorted[mid];
	unsorted[mid] = unsorted[start];
	unsorted[start] = temp;
    }
    else if ( (unsorted[end] >= unsorted[start] && unsorted[end] <= unsorted[mid]) ||
	      (unsorted[end] <= unsorted[start] && unsorted[end] >= unsorted[mid]))
    {
	pIndex=end;
	display();
	temp = unsorted[end];
	unsorted[end] = unsorted[start];
	unsorted[start] = temp;
    }
    else
    {
	pIndex=start;
	display();
    }

    pivot = unsorted[0 + start];    //why?
    printf("pivot: %lu",pivot);//d
    for (i = start + 1, j = start + 1; j < start + arr_len; j++)
    {
	if (unsorted[j] <= pivot)
	{
	    /* mark pair to be swapped */
	    pair[0]=i;
	    pair[1]=j;

	    /* display before swap */
	    display();
	    usleep(200000);

	    /* swap */
	    temp = unsorted[j];
	    unsorted[j] = unsorted[i];
	    unsorted[i] = temp;

	    /* update display after swap */
	    display();
	    usleep(200000);

	    /* no marked bars!! */
	    pair[0]=-1;
	    pair[1]=-1;

	    i++;
	}
    }
    
    temp = unsorted[i - 1];
    unsorted[i - 1] = unsorted[0 + start];
    unsorted[0 + start] = temp;

    /* update display */
    display();
    usleep(200000);
    // glutPostRedisplay();    
//    getchar();
//    while(!keyPress)
//	;
   
    quickSort (unsorted, 0 + start, i - 2);
    quickSort (unsorted, i, end);
}

void idleFunc(void)
{
/*    if (done==0)
    {
	done=1;
	quickSort(num,0,19);
//	done=1;
}*/
}

void printNos(void)
{
    int i;
    for(i=0;i<20;i++)
	printf("%lu ",num[i]);

    printf("\n");
}

void genRandNos(void)
{
    count=60;
    int i;
    num=(unsigned long int *)malloc(count*sizeof(unsigned long int));

    for(i=0;i<count;i++)
	num[i]=rand()%100+1;
}
