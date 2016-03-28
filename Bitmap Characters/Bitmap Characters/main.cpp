/*
I am using free glut Library
Its a basic program to show how to set the openGL Window and some basic function

Happy Coding
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

bool init()
{

	glClearColor(0, 0, 0, 1); //set the backgroung to black

	glMatrixMode(GL_MODELVIEW); //loading ModelView Matrix
	glLoadIdentity();

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

	char *c = "DEVASHISH";

	glColor3f(1, 0, 0);
	glRasterPos2f(100, 250);
	for (int i = 0; i < 9; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);

	glFlush();
}



void reshape(int w, int h) //function to call when the screen is reshaped
{
	double w2h = (h> 0) ? (double)w / h : 1;
	glViewport(0, 0, w, h); //setting the viewport i.e. where the primitive should be displayed

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -100, 100); //set the orthogonal view for the view port

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


int main(int argc, char*argv[])
{
	glutInit(&argc, argv); //initialise glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //setting the Display mode
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
