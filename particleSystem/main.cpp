#include<freeglut.h>

#define MAX_PARTICLES 1000

float slowDown = 1.0f;
float xspeed;
float yspeed;
GLuint loop;
GLuint col;
GLuint delay;
GLuint zoom = 4.0f;
typedef struct
{
	bool active;
	float life;
	float fade;
	float r;
	float g;
	float b;

	float x;
	float y;
	float z;

	float xi;
	float yi;
	float zi;

	float xg;
	float yg;
	float zg;
}particles;

particles particle[MAX_PARTICLES];

static GLfloat colors[12][3] =    //Rainbow Of Colors 
{ {1.0f,0.5f,0.5f},{1.0f,0.75f,0.5f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},  {0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},  {0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f} };


bool init()
{
	glClearColor(1, 1, 1, 1);

	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();

	glViewport(0, 0, 500, 500);
	glOrtho(-2, 2, -2, 2, 10, -10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);


	for (loop = 0; loop < MAX_PARTICLES; loop++);
	{
		particle[loop].active = true;
		particle[loop].life = 1.0f;
		particle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;
	
		particle[loop].r = colors[(loop + 1) / (MAX_PARTICLES / 12)][0];
		particle[loop].g = colors[(loop + 1) / (MAX_PARTICLES / 12)][1];
		particle[loop].b = colors[(loop + 1) / (MAX_PARTICLES / 12)][2];

		particle[loop].xi = float((rand() % 50) - 26.0f) * 10.0f;
		particle[loop].yi = float((rand() % 50) - 25.0f) * 10.0f;
		particle[loop].zi = float((rand() % 50) - 25.0f) * 10.0f;

		particle[loop].xg = 0.0f;
		particle[loop].yg = -0.8f;
		particle[loop].zg = 0.0f;
	}


	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	return false;

	return true;
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glViewport(0, 0, 500, 500);
	glOrtho(-2, 2, -2, 2, 10, -10);

	glMatrixMode(GL_MODELVIEW);
	
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	/*for (loop = 0; loop < MAX_PARTICLES; loop++)
	{
		if (particle[loop].active)
		{

			float x = particle[loop].x;
			float y = particle[loop].y;
			float z = particle[loop].z + zoom;

			glColor4f(particle[loop].r, particle[loop].g, particle[loop].b, particle[loop].life);
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(x + 0.5f, y + 0.5f, z);
			glVertex3f(x - 0.5f, y + 0.5f, z);
			glVertex3f(x + 0.5f, y - 0.5f, z);
			glVertex3f(x - 0.5f, y - 0.5f, z);
			glEnd();

			particle[loop].x += particle[loop].xi / (slowDown * 1000);
			particle[loop].y += particle[loop].yi / (slowDown * 1000);
			particle[loop].z += particle[loop].zi / (slowDown * 1000);

			particle[loop].xi += particle[loop].xg;
			particle[loop].yi += particle[loop].yg;
			particle[loop].zi += particle[loop].zg;

			particle[loop].life -= particle[loop].fade;

			if (particle[loop].life < 0.0f)
			{
				particle[loop].life = 1.0f;
				particle[loop].fade = float(rand() % 100) / 1000 + 0.003f;

				particle[loop].x = 0;
				particle[loop].y = 0;
				particle[loop].z = 0;

				particle[loop].xi = xspeed + float((rand() % 60) - 32.0f);
				particle[loop].yi = yspeed + float((rand() % 60) - 30.0f);
				particle[loop].zi = float((rand() % 60) - 30.0f);

			}
		}
	}*/


	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0.5f, 0.5f, 0);
	glVertex3f(- 0.5f, 0.5f, 0);
	glVertex3f(0.5f, - 0.5f, 0);
	glVertex3f(- 0.5f,  - 0.5f, 0);
	glEnd();
	glutSwapBuffers();
}


int main(int argc, char ** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Particles");

	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		particle[i].x = 0.0f;
		particle[i].y = 0.0f;
		particle[i].z = 0.0f;

	}

	xspeed = 0;
	yspeed = 0;

	if (!init())
		return -1;

	
	glutReshapeFunc(reshape);
	glutDisplayFunc(render);
	glutMainLoop();

	return 0;
}


