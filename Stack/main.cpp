/*
I am using free glut Library
Its a basic program to show how to set the openGL Window and some basic function

Happy Coding .....
*/


#include<stdlib.h>
#include<cstdio>
#include<iostream>
#include<freeglut.h>
#include"element.h"
using namespace std;

int tot = -1;
int SCREEN_WIDTH = 500; //Width of the screen
int SCREEN_HEIGHT = 500; //height of the screen
char *WindowName = "Hello OpenGL"; //Name of the window
double dim = 2; //dimension for viewing triangle
int newY = 100;
char *a[10];
#define MAX 10
stackElement e[MAX];

bool init()
{

	glClearColor(0, 0, 0, 1); //set the backgroung to black
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glOrtho(0, 500, 0, 500, -100, 100);

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

	if (tot > -1) {
	for (int n = 0; n < tot; n++)
	{
		e[n].render();
		glFlush();
	}
}
}


void push()
{

	if (tot < MAX) {

		char c[100];
		
		tot++;
		if (tot == 0) {
			cout << "\nEnter Element to Push: ";
			cin >> c;
			cout << endl;
			e[tot].push(250, newY, c);
			newY+= 50;
			cout << e[tot].x <<"\t"<<e[tot].y<<endl;
			render();
		}
		else {
			cout << "\nEnter Element to Push: ";
			cin >> c;
			cout << endl;
			e[tot].push(250, newY, c);
			newY += 50;
			render();
		}


	}

	glClear(GL_COLOR_BUFFER_BIT);
}


void keyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'P' | 'p': push();
		break;
	}
}


void reshape(int w, int h) //function to call when the screen is reshaped
{
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	glViewport(0, 0, w, h);
	glOrtho(0, w, 0, h, -100, 100);

	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


int main(int argc, char*argv[])
{


	for (int i = 0; i < MAX; i++)
	{
		e[i].setWH(100, 25);

	}

	glutInit(&argc, argv); //initialise glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //setting the Display mode
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); //Setting the window size
	glutCreateWindow(WindowName);//Setting the name of the window

	if (!init()) //check for the error
	{
		cout << "Error" << endl;
		return -1;
	}
	glClear(GL_COLOR_BUFFER_BIT);

	glutDisplayFunc(render);  //register display func
	glutReshapeFunc(reshape); //register reshape func
	glutKeyboardFunc(keyBoard);
	glutMainLoop(); //loop the main section

	return 0;
}
