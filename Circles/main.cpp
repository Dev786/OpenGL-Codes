/*
Circle 
Happy Coding .....
*/


#include<stdlib.h>
#include<cstdio>
#include<iostream>
#include<freeglut.h>
#include"circle.h"
using namespace std;

int SCREEN_WIDTH = 500; //Width of the screen
int SCREEN_HEIGHT = 500; //height of the screen
char *WindowName = "Hello OpenGL"; //Name of the window
double dim = 2; //dimension for viewing triangle



bool init()
{

	glClearColor(1, 1, 1, 0); //set the backgroung to black

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
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT); //resetting the screen
	glLoadIdentity(); //load identity matrix to model view
	
	//circle(0, 0,0.5);
	
	glColor3f(1, 0, 0);
	glViewport(250, 250, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	TooManycircle(0, 0, 1);
	glFlush(); //put everything to screen
	
	glColor3f(0, 1, 1);
	glViewport(0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	TooManycircle(0, 0, 0.75);
	glFlush(); //put everything to screen

	glColor3f(0, 1, 1);
	glViewport(250, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	TooManycircle(0, 0, 0.5);
	glFlush(); //put everything to screen

	glColor3f(0.5, 0, 0.5);
	glViewport(0, 250, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	TooManycircle(0, 0, 0.4);
	glFlush(); //put everything to screen

	
}



void reshape(int w, int h) //function to call when the screen is reshaped
{
	double w2h = (h> 0) ? (double)w / h : 1;
	glViewport(0, 0, w, h); //setting the viewport i.e. where the primitive should be displayed

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-dim*w2h, +dim*w2h, -dim, +dim, -dim, +dim); //set the orthogonal view for the view port

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
