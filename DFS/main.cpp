#include<stdlib.h>
#include<iostream>
#include<freeglut.h>

int SCREEN_HEIGHT= 500;
int SCREEN_WIDTH= 500;

int posX = 250;
int posY = 250;

int k = 0;
int a[500][500];
bool visited[500];

void init()
{
	glClearColor(0, 0, 0, 1);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glOrtho(0, 500, 0, 500,-100,100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void initialisePath()
{

	for (int i = 0; i < 500; i++)
		for (int j = 0; j < 500; j++)
		{
			a[i][j] = 1 ;
		}
	
	for (int i = 0; i < 500; i++)
	{
		visited[i] = false;
	}

}


void dfsR(int j, int from,int n)
{
	if (n > 2400)
		return;

	visited[j] = true;

	glBegin(GL_POINTS);
	glVertex2i(from, j);
	glEnd();
	glFlush();
	Sleep(2);
	for (int i = 0; i < 500; i+=2)
	{
		if (a[j][i] == 1)
			dfsR(i, j,n+1);
	}
}

void dfs(int j,int n)
{
	if (n > 2400)
		return;

	visited[j] = true;
	glBegin(GL_POINTS);
	glVertex2i(j, j);
	glEnd();
	glFlush();
	Sleep(2);
	for (int i = 0; i < 500; i+=2)
	{
		if ( a[j][i] == 1)
		{
			dfsR(i, j,n+1);
		}
	}
}


void reshape(int w, int h)
{
	glClearColor(0, 0, 0, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glOrtho(0, 500, 0, 500, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	dfs(40,k);

	glFlush();
	
}


void main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("DFS");

	init();
	initialisePath();
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutMainLoop();

}

