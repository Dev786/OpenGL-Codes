#include<freeglut.h>
int SCREEN_WIDTH = 500;
int SCREEN_HEIGHT = 500;


void drawCube()
{

	glClearColor(0.0, 0.0, 0.0, 0.0);
	float difamb[] = { 122,11,123,1 };
	glBegin(GL_QUADS);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, difamb);
	
	//front face
	glNormal3f(0, 0, 1);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);


	//back face
	glNormal3f(0, 0, -1);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);


	//left face
	glNormal3f(-1, 0, 0);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);


	//right face
	glNormal3f(1, 0, 0);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);


	//top face
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);

	glColor3f(0, 1, 1);
	//bottom face
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);

	glEnd();

}

bool init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0, 0, 0,0);
	
	//glEnable(GL_LIGHTING);

	glEnable(GL_DEPTH_TEST);



	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
//	glEnable(GL_COLOR_MATERIAL);



	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	float dif[] = { 1,1,1,1 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, dif);

	float amb[] = { 0.2,0.2,0.2,1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);



	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		return false;
	}
	
	return true;
}

int r = 0;

void render()
{

	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	float pos[] = {1,0,-1,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);


	glBegin(GL_QUADS);
	
	//front face
	glColor4f(0, 0, 1, 0.75);
	glVertex3f(-0.5, -0.5, -0.25);
	glVertex3f(0.5, -0.5, -0.25);
	glVertex3f(0.5, 0.5, -0.25);
	glVertex3f(-0.5, 0.5, -0.25);


	//back face
	glColor4f(1, 0, 0, 0.5);
	glVertex3f(-0.75, -0.75, -1);
	glVertex3f(0.75, -0.75, -1);
	glVertex3f(0.75, 0.75, -1);
	glVertex3f(-0.75, 0.75, -1);
	glEnd();
	

	glutSwapBuffers();
	r++;
	Sleep(10);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("ALPHA BLENDING");

	if (!init())
	{
		return 0;
	}

	glutDisplayFunc(render);
	glutMainLoop();

	return 0;
}



