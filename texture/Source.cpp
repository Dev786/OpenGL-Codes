/*
I am using free glut Library
Its a basic program to show how to set the openGL Window and some basic function

Happy Coding .....
*/


#include<stdlib.h>
#include<il.h>
#include<ilu.h>
#include<cstdio>
#include<iostream>
#include<conio.h>
#include<freeglut.h>
#include "LTexture.h"
using namespace std;

int SCREEN_WIDTH = 500; //Width of the screen
int SCREEN_HEIGHT = 500; //height of the screen
char *WindowName = "Hello OpenGL"; //Name of the window
double dim = 2; //dimension for viewing triangle
LTexture gCheckerBoardTexture;


bool init()
{
	//Set the viewport
	glViewport(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);

	//Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Initialize clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//Enable texturing
	glEnable(GL_TEXTURE_2D);
	//Check for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		_getch();
		return false;
	}

	ilInit();
	ilClearColour(255, 255, 255, 000);

	//Check for error
	ILenum ilError = ilGetError();
	if (ilError != IL_NO_ERROR)
	{
		printf("Error initializing DevIL! %s\n", iluErrorString(ilError));
		return false;
	}

	return true;
}


bool loadMedia()
{
	const int CHECKERBOARD_WIDTH = 128;
	const int CHECKERBOARD_HEIGHT = 128;
	const int CHECKERBOARD_PIXEL_COUNT = CHECKERBOARD_WIDTH * CHECKERBOARD_HEIGHT;
	GLuint checkerBoard[CHECKERBOARD_PIXEL_COUNT];

	for (int i = 0; i < CHECKERBOARD_PIXEL_COUNT; ++i)
	{
		//Get the individual color components
		GLubyte* colors = (GLubyte*)&checkerBoard[i];
		if (i / 128 & 16 ^ i % 128 & 16)
		{
			//Set pixel to white
			colors[0] = 0xFF;
			colors[1] = 0xFF;
			colors[2] = 0xFF;
			colors[3] = 0xFF;
		}
		else
		{
			//Set pixel to red
			colors[0] = 0xFF;
			colors[1] = 0x00;
			colors[2] = 0x00;
			colors[3] = 0xFF;
		}
	}

	//if (!gCheckerBoardTexture.getImageFromPixel32(checkerBoard, CHECKERBOARD_WIDTH, CHECKERBOARD_HEIGHT))
		//return false;

	if(gCheckerBoardTexture.loadTextureFromFile("dr.jpg"));
	return true;

	return false;

		
	}



void render()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//Calculate centered offsets

	//Render checkerboard texture
	gCheckerBoardTexture.render(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);

	//Update screen
	glutSwapBuffers();
}



void reshape(int w, int h) //function to call when the screen is reshaped
{
	SCREEN_WIDTH = w;
	SCREEN_HEIGHT = h;
	glViewport(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);

	//Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

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
		_getch();
		return -1;
	}
	if (!loadMedia())
	{
		printf("Unable to load media!\n");
		_getch();
		return 2;
	}
	glutDisplayFunc(render);  //register display func
	glutReshapeFunc(reshape); //register reshape func
	glutMainLoop(); //loop the main section

	return 0;
}
