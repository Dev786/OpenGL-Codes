#include<stdlib.h>
#include<freeglut.h>

int SCREEN_HEIGHT = 0;
int SCREEN_WIDTH = 0;
class particles
{
public: 
	double x;
	double y;

	float red;
	float gree;
	float blue;

	float life;

	float speedY;
	float speedX;
};

particles particle[10000];

float seed = 0;
float r = 0;
float g = 0;
float b = 0;
int life = 0;

void init()
{

	for (int i = 0; i < 1000; i++)
	{

		particle[i].speedY = float(rand() % 3);
		particle[i].speedX = float(rand() % 3);
		particle[i].x = float(rand() % 500 );
		particle[i].y = float(rand() % 500);
		particle[i].life = 1;

	}
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	glViewport(0, 0, 500, 500);
	glOrtho(-500, 500, -500, 500, -100, 100);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(int w, int h)
{
	SCREEN_WIDTH = w;
	SCREEN_HEIGHT = h;

	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h );
	glOrtho(-w, w, -h, h, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void render()
{
	int i = 0;
	do
	{
		srand(seed);
		seed += 0.1f,
		r += 0.1;
		b += 0.2;
		g += 0.3;

		if (r > 1.0f)
		{
			r = float(rand() % 2) - 0.7;
		}

		if (g > 1.0f)
		{
			r = float(rand() % 2) - 0.8;
		}
		if (r > 0.5f)
		{
			r = float(rand() % 2) - 0.3;
		}

		glColor4f(particle[i].red, particle[i].gree, particle[i].blue,particle[i].life);

		glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(particle[i].x + 0.3, particle[i].y + 0.3);
		glVertex2f(particle[i].x - 0.3, particle[i].y + 0.3);
		glVertex2f(particle[i].x + 0.3, particle[i].y - 0.3);
		glVertex2f(particle[i].x - 0.3, particle[i].y - 0.3);
		glEnd();

		glFlush();
		
		particle[i].red = r;
		particle[i].gree = g;
		particle[i].blue = b;

		particle[i].x += particle[i].speedX;
		particle[i].y += particle[i].speedY;
		particle[i].life = 0.01f;

	} while (i < 1000);

	glutPostRedisplay();
}

void main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("particle");

	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(render);
	glutMainLoop();

}
