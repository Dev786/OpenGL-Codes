/*
I am using free glut Library
Its a basic program to show how to set the openGL Window and some basic function

Happy Coding .....
*/


#include<stdlib.h>
#include<cstdio>
#include<iostream>
#include<freeglut.h>

using namespace std;

int SCREEN_WIDTH = 500; //Width of the screen
int SCREEN_HEIGHT = 500; //height of the screen
char *WindowName = "Hello OpenGL"; //Name of the window
double dim = 2; //dimension for viewing triangle
int ch; //for Primitive choice
int sizeX = 5;
int sizeY = 5;


bool init()
{

	glClearColor(0, 0, 0, 1); //set the backgroung to black

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glOrtho(-sizeX, sizeX, -sizeY,sizeY ,-100,100);

	glMatrixMode(GL_MODELVIEW); //loading ModelView Matrix
	glLoadIdentity();

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	GLenum error = glGetError(); //Check for the error

	if (error != GL_NO_ERROR) //if error is there
	{
		return false; //returning error has been detected
	}

	return true; //returning everything is fine go on
}






void render() //display function 
{  
	glClear(GL_COLOR_BUFFER_BIT); //resetting the screen
	glLoadIdentity(); //load identity matrix to model view
	
	GLfloat ambientLight[] = { 1.0f,0.0f,0.0f,1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientLight);

	  
	GLfloat light0[] = {     0.0f,0.5f,0.0f,1 };  
	GLfloat position0[] = { 0,0,5,1};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);

	GLfloat light1[] = { 0.0f,0.0f,1.0f,1 };
	GLfloat position1[] = { 0,0,5,1 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light0);
	glLightfv(GL_LIGHT1, GL_POSITION, position0);



	glBegin(GL_QUADS);

	glVertex2f(-2.5, -2.5);
	glVertex2f(2.5, -2.5);
	glVertex2f(2.5, 2.5);
	glVertex2f(-2.5, 2.5);

	glEnd();
	

	glFlush(); //put everything to screen
	glutSwapBuffers();//swapping the two buffers "Front and Back"
}


void reshape(int w, int h) //function to call when the screen is reshaped
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h); //setting the viewport i.e. where the primitive should be displayed
	glOrtho(-sizeX, sizeX, -sizeY, sizeY, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


int main(int argc, char*argv[])
{


	glutInit(&argc, argv); //initialise glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //setting the Display mode
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); //Setting the window size
	glutCreateWindow(WindowName);//Setting the name of the window

	if (!init()) //check for the error
	{
		cout << "Error" << endl;
		return -1;
	}

	glutDisplayFunc(render);  //register display func
	glutReshapeFunc(reshape); //register reshape func
	glutMainLoop(); //loop the main section

	return 0;
}
