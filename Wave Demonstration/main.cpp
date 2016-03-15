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
char *WindowName = "Waves"; //Name of the window
double dim = 2; //dimension for viewing triangle
int time = 10; //set the sleep Time

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


	char *c = "CHOOSE 1. S or s for sin , 2. C or c for cos, 3. t or T for tan";
	cout << c;

	return true; //returning everything is fine go on
}

float x = -2;
float y = 0;

int ch;

void sine()
{
	glClearColor(0, 0, 0, 1);
	for (float r = 0; r <= 400; r++)
	{
		float rad = r*(3.14 / 180);
		y = 0.5 * sin(rad);
		glBegin(GL_POINTS);
		glVertex2f(x += 0.01, y);
		glEnd();
		Sleep(time);
		glFlush();
		glutSwapBuffers();
	}

	glutPostRedisplay();
}

void cosine()
{

	glClearColor(0, 0, 0, 1);
	for (float r = 0; r <= 400; r++)
	{
		float rad = (90 - r)*(3.14 / 180);
		y = 0.5 * sin(rad);
		glBegin(GL_POINTS);
		glVertex2f(x += 0.01, y);
		glEnd();
		Sleep(time);
		glFlush();
		glutSwapBuffers();
	}

	glutPostRedisplay();
}

void tanF()
{
	glClearColor(0, 0, 0, 1);

	for (float r = 0; r <= 400; r++)
	{
		float rad = r*(3.14 / 180);
		y = 0.5 * tan(rad);
		glBegin(GL_POINTS);
		glVertex2f(x += 0.01, y);
		glEnd();
		Sleep(time);
		glFlush();
		glutSwapBuffers();
	}


	glutPostRedisplay();
}
void render() //display function 
{
	glClear(GL_COLOR_BUFFER_BIT); //resetting the screen
	glLoadIdentity(); //load identity matrix to model view
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

void keyBoardFunc(unsigned char key, int x, int y)
{
	switch ((key))
	{
	case 't' | 'T':tanF();
		break;
	case 's' | 'S':sine();
		break;
	case 'c' | 'C':cosine();
		break;
	default:
		break;
	}
}

int main(int argc, char*argv[])
{
	cout << "\nEnter Time to slow down animation in milli Second: ";
	cin >> time;



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
	glutKeyboardFunc(keyBoardFunc);
	glutMainLoop(); //loop the main section

	return 0;
}
