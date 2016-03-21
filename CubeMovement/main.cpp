/*
I am using free glut Library
Its a basic program to show how to set the openGL Window and some basic function

Happy Coding
*/





#include<stdlib.h>
#include<cstdio>
#include<iostream>
#include<glew.h>
#include<gl\GL.h>
#include<freeglut.h>
#include "Header.h"

using namespace std;
bool moveX[2] = { false,false }, moveZ[2] = { false,false };

DCube c(0, 0, 0, 100);

int SCREEN_WIDTH = 500; //Width of the screen
int SCREEN_HEIGHT = 500; //height of the screen
char *WindowName = "Hello OpenGL"; //Name of the window
double dim = 10; //dimension for viewing triangle

void update()
{
	if (moveZ[0])
	{
		c.Movecube(0, 0, 2);
		moveZ[0] = false;
	}

	else if (moveZ[1])
	{

		c.Movecube(0, 0, -2);
		moveZ[1] = false;
	}

	else if (moveX[0])
	{

		c.Movecube(2, 0, 0);
		moveX[0] = false;
	}
	
	else 	if (moveX[1])
	{

		c.Movecube(-2, 0, 0);
		moveX[1] = false;
	}
}




bool init()
{

	glClearColor(0, 0, 0, 1); //set the backgroung to black
	
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-SCREEN_WIDTH/10, SCREEN_WIDTH / 10, SCREEN_WIDTH / 10, -SCREEN_WIDTH / 10, -100, 100);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



	glMatrixMode(GL_MODELVIEW); //loading ModelView Matrix
	glTranslatef(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,0);
	
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POLYGON_SMOOTH);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLenum error = glGetError(); //Check for the error

	if (error != GL_NO_ERROR) //if error is there
	{
		return false; //returning error has been detected
	}

	return true; //returning everything is fine go on
}





void render() //display function 
{
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //resetting the screen
	glLoadIdentity(); //load identity matrix to model view


	GLfloat color[] = { 1,0,0,1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, color);

	glColor3f(1, 0, 0);
	c.drawCube();
	glFlush();
	glutSwapBuffers();//swapping the two buffers "Front and Back"

}



void reshape(int w, int h) //function to call when the screen is reshaped
{
	
	glViewport(0, 0, w, h); //setting the viewport i.e. where the primitive should be displayed

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (h == 0)
		h = 1;

	glOrtho(-w,w, h, -h, -1000, 1000);

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POLYGON_SMOOTH);
	glEnable(GL_MULTISAMPLE);

	

}

void specialFunction(int key,int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP: moveZ[0] = true;
		update();
		break;
	case GLUT_KEY_DOWN: moveZ[1] = true;
		update();
		break;
	case GLUT_KEY_RIGHT: moveX[0] = true;
		update();
		break;
	case GLUT_KEY_LEFT: moveX[1] = true;
		update();
		break;
	}
}


void timerFunc(int val)
{
	render();
	glutTimerFunc(2, timerFunc, 0);
}


int main(int argc, char*argv[])
{
	glutInit(&argc, argv); //initialise glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH|GLUT_MULTISAMPLE); //setting the Display mode
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); //Setting the window size
	glutCreateWindow(WindowName);//Setting the name of the window

	if (!init()) //check for the error
	{
		cout << "Error" << endl;
		return -1;
	}

	glutSpecialFunc(specialFunction);
	glutDisplayFunc(render);  //register display func
	glutReshapeFunc(reshape); //register reshape func
	glutTimerFunc(1000 / 60, timerFunc, 0);
	glutMainLoop(); //loop the main section

	return 0;
}
