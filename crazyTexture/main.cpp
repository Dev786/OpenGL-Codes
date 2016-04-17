
#include<iostream>
#include<freeglut.h>
#include<il.h>
#include"initialiseArray.h"
#include"loadImage.h"
#include<conio.h>

LTexture text[65];
bool wait = false;
bool start = true;
using namespace std;
int i = 0;
const string  imageName[65] = { "tex.jpg","1.jpg" , "2.jpg" , "3.jpg" , "4.jpg" , "5.jpg" , "6.jpg" , "7.jpg" , "8.jpg" , 
"9.jpg" , "10.jpg" , "11.jpg" , "12.jpg" , "13.jpg" , "14.jpg" , "15.jpg" , "16.jpg" , 
"17.jpg" , "18.jpg" , "19.jpg" , "20.jpg" , "21.jpg" , "22.jpg" , "23.jpg" , "24.jpg" , 
"25.jpg" , "26.jpg" , "27.jpg" , "28.jpg" , "29.jpg" , "30.jpg" , "31.jpg" , "32.jpg" , 
"33.jpg" , "34.jpg" , "35.jpg" , "36.jpg" , "37.jpg" , "38.jpg" , "39.jpg" , "40.jpg" , 
"41.jpg" , "42.jpg" , "43.jpg" , "44.jpg" , "45.jpg" , "46.jpg" , "47.jpg" , "48.jpg" , 
"49.jpg" , "50.jpg" , "51.jpg" , "52.jpg" , "53.jpg" , "54.jpg" , "55.jpg" , "56.jpg",
"57.jpg" , "58.jpg" , "59.jpg" , "60.jpg" , "61.jpg" , "62.jpg" , "63.jpg" , "64.jpg" };

int SCREEN_HEIGHT = 800;
int SCREEN_WIDTH = 800;


bool init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glOrtho(0, 200, 200, 0, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(10, 10,0);
	glClearColor(0, 0, 0, 1);


	glEnable(GL_TEXTURE_2D);

	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		cout << "\nError in init"<<endl;
		return false;
	}

	
	ilInit();
	ilClearColor(255, 255, 255, 000);
	ILenum  err = ilGetError();

	if (err != IL_NO_ERROR)
	{
		cout << "\nError in IL"<<endl;
		return false;
	}

	return true;
}


void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	glOrtho(0, w, h, 0, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	SCREEN_WIDTH = w;
	SCREEN_HEIGHT = h;
}


void render()
{


	glClear(GL_COLOR_BUFFER_BIT);

	if (start)
	{

		for (int i = 1; i <= 56; i++)
		{
			text[i].render();
		}

		glutSwapBuffers();
		Sleep(1000);
		start = false;
	}

	
	if (i == 360)
	{
		
		for (int i = 1; i <= 56; i++)
		{

			text[i].reset();
			text[i].render();
		}

		for (int i = 1; i <= 56; i++)
		{
			text[i].render();
		}
		glFlush();
		glutSwapBuffers();
		Sleep(1000);
		i = 0;
	}



	if (wait)
	{
		Sleep(50);
		wait = false;
	}

	for (int i = 1; i <= 56; i++)
	{
		text[i].moveIt();
	}

	glutSwapBuffers();


	Sleep(20);
	i++;

	glutPostRedisplay();
}


bool loadMedia()
{

	bool loaded;
	for (int i = 1; i <= 64; i++)
	{
		loaded = text[i].loadTextureFromImage(imageName[i]);
		if (!loaded)
			break;
	}


	if (!loaded)
	{
		cout << "\nError Loading Texture";
		return false;
	}

	return true;
}

int main(int argc, char ** argv)
{

	int k = 1;
	int y = 200;
	for (int i = 0; i < 8; i++)
	{
		int x = 200;
		for (int j = 0; j < 8; j++)
		{
			text[k].y = y;
			text[k].x = x;
			x += 40;
			text[k].setInitialPosition();
			text[k].setWH(20, 20);
			k++;
		}
		y += 40;
	}


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("CrazyTexture");

	if (!init())
	{

		return -1;
	}

	if (!loadMedia()) {
		return -1;
	}

	glutReshapeFunc(reshape);
	glutDisplayFunc(render);
	glutMainLoop();

	return 0;
}
