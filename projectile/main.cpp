#include<freeglut.h>
#include<math.h>
int SCREEN_HEIGHT = 1000;
int SCREEN_WIDTH = 1000;
int v0 = 4;
int g = 10;
float t = 0;
int initialX0 = 0;
int angle = 45;




class position
{
public: float x, y,angle;
		bool reached;
		position()
		{
			x = -600, y = 0;
			angle = rand() % 91;
			reached = false;

		}
};

const int num = 10;
position p[num+1];


bool init()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glOrtho(-500, 500, -500, 500, -2, 2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	GLenum err = glGetError();

	if (err != GL_NO_ERROR)
		return false;

	return true;

}

void reshape(int w, int h)
{
	
	glutFullScreen();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	glOrtho(-w, w, -h, h, -2, 2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);

	glFlush();
}

bool first = true;

void render()
{
	
	//glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();


	glTranslatef(0, -200, 0);
	
	//function


	
	for (int i = 0; i <= num; i++) {

		if (!p[i].reached) {
		float angR = (3.14 / 180)*p[i].angle;
		p[i].x += v0*cos(angR);
		p[i].y += v0*sin(angR) - g*t;
		first = false;
		glPointSize(2);
		glBegin(GL_POINTS);
		glVertex2f(p[i].x, p[i].y);
		glEnd();
		glFlush();
		}
		if (p[i].y < 0)
			p[i].reached = true;
		glFlush();
	}

	t += 0.001;
	glutSwapBuffers();
}

void Timer(int val)
{
	render();
	glutTimerFunc(20, Timer, 0);
}



void main(int argc,char ** argv)
{

	//p[1].angle = 0;
	//p[2].angle = 30;
	//p[3].angle = 45;
	//p[4].angle = 60;
	//p[5].angle = 90;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("PROJECTILE");
	if (!init)
		return;

	glutReshapeFunc(reshape);
	glutDisplayFunc(render);
	glutTimerFunc(20, Timer, 0);
	glutMainLoop();
}