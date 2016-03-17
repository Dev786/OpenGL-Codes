
#include<iostream>
#include<glew.h>
#include<gl\GL.h>
#include<freeglut.h>
using namespace std;

int SCREEN_HEIGHT = 500;
int SCREEN_WIDTH = 500;

bool init()
{

	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-SCREEN_WIDTH, SCREEN_WIDTH, -SCREEN_HEIGHT, SCREEN_HEIGHT, -100, 100);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0, 0, 0, 0);

	glColor3f(0, 1, 1);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_MULTISAMPLE);
	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		cout << "\n" << gluGetString(error) << endl;
		return false;
	}

	return true;
}

int theta = 0;

void rotate()
{
	glRotatef(theta++, 0, 0, 1);
}
void flowerPattern()
{
	float xP = 0, yP = 0, yN = 0, xN = 0;
	float in = 0.5;
	float r = 50;
	glPointSize(1);
	for (float theta = 0; theta <= 180; theta += 0.5) {
		float thetaR = (3.14 / 180) * theta;

		glBegin(GL_POINTS);
		glVertex2f(xP+=in, r*sin( thetaR));
		glVertex2f(xN-= in, r*sin(thetaR));
		glVertex2f(r*sin(thetaR),yP+=in);
		glVertex2f(r*sin(thetaR),yN-=in);


		glVertex2f(xP += in,-r*sin(thetaR));
		glVertex2f(xN -= in, -r*sin(thetaR));
		glVertex2f(-r*sin(thetaR), yP += in);
		glVertex2f(-r*sin(thetaR), yN -= in);
		glEnd();

	}


}

int r = 0;
void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glRotatef(r++, 0, 0, 1);
	flowerPattern();
	glutSwapBuffers();
	glutPostRedisplay();
}


int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB | GLUT_MULTISAMPLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Flower");
	
	if (!init())
	{
		return 0;
	}

	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}




