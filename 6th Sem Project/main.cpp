#include<iostream>
#include<time.h>
#include<freeglut.h>
#include<IL\ilu.h>
#include<IL\il.h>

#include"Texture.h"

Texture tex;
bool dance = false;
founTainBase base;
int i = 0;
float x, y;
float ang = 0;

bool init()
{
	glClearColor(0, 0, 0, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	glViewport(0, 0, 500, 500);
	glOrtho(0, 500, 500, 0, -100, 100);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	ilInit();
	ilClearColor(255, 255, 255, 000);

	ILenum err = ilGetError();

	if (err != IL_NO_ERROR)
	{
		std::cout << "\nIL Error\n";
		return false;
	}

	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{

		std::cout << "\nGL Error\n";
		return false;
	}
	
	return true;
}


void render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
	//for (int j = 0; j < i; j++) {
		tex.fountain();
	//}
	glutSwapBuffers();
}


void Specialkey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_CTRL_L:dance = true;
		break;
	case GLUT_KEY_CTRL_R: dance = false;
		break;
	}
}


void reshape(int w, int h)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	glViewport(0, 0, w, h);
	glOrtho(0, w, h, 0, -100, 100);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



bool loadMedia()
{
	if (!tex.LoadTextureFromPath("mainParticle.png"))
		return false;

	return true;
}




void MouseMotion(int x, int y)
{
	if (i < 20000) {
		tex.setXY(i, x, y);
		i++;
	}

}
//GLFountainTimerFunc

void FountainTimer(int val)
{
	render();
	glutTimerFunc(1000 / 60, FountainTimer, 0);
}



void bday(int val)
{
	int delay = false;
	for (int j = 0; j < i;j++)
		if (dance) {
			tex.particle[j].bdayDance();

		}
	glutTimerFunc(80, bday, 0);

}




int main(int argc, char ** argv)
{

	srand(time(NULL));
	//tex.initialise();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutCreateWindow("particle");

	if (!init())
	{
		return -1;
	}
	
	if (!loadMedia())
		return false;
    glutFullScreen();
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutMotionFunc(MouseMotion);
	glutTimerFunc(1000/20, FountainTimer, 0);
	glutTimerFunc(80, bday, 0);
	glutSpecialFunc(Specialkey);
	glutMainLoop();
}