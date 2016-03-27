#include<iostream>
#include<freeglut.h>
#include<math.h>
#include<conio.h>
int SCREEN_HEIGHT = 500;
int SCREEN_WIDTH = 500;
int MAX = 1000;
int incAng = 0;
float PointedAngle = 0;
int i = 0;
int velocity = 5;
bool input = true;
bool shotB = false;
bool updateB = false;

class position
{
public:float x, y, angle;
	   int velocity;
	   bool dead = false;
	   position() {
		   this->x = 0;
		   this->y = 0;
	   }
	   ~position()
	   {
		   //std::cout << "\nRemoved";
	   }
	   void remove()
	   {
		   delete this;
	   }
};



//enemy

class enemy
{
private: position p;
		 bool dead;
public:
	enemy()
	{
		p.x = 0;
		p.y = 0;
		p.dead = false;
	}
	void move()
		{
			p.y += 2;
		}
		void setXY(float x, float y)
		{
			p.x = x;
			p.y = y;
		}
		void drawEnemy()
		{
			glLoadIdentity();
			glPointSize(10);
			glBegin(GL_POINTS);
			glVertex2f(p.x, p.y);
			glEnd();
			glFlush();
		}
		void update(float y,position  bullet)
		{
			checkCollision(bullet);
			if (!dead) {
				p.y += y;
				setXY(p.x, p.y);
				drawEnemy();
			}
		}

		void checkCollision(position bullet)
		{
		
			int bX = (int)(SCREEN_WIDTH/4 - bullet.x);
			int bY = (int)(SCREEN_HEIGHT/4 - bullet.y);

			std::cout << "\nBullet: " << bX << " " << bY<<std::endl;
			std::cout << "\nenemy: " << p.x << " " << p.y << std::endl;
			
			glPushMatrix();
			
			if ((int)bullet.x == (int)p.x&& (int)bullet.y == (int)p.y)
			{
				std::cout << "\nCollision Detected"<<std::endl;
				dead = true;
			}		
		}
};

enemy e;

//



position gun,pointed;
position bullet[1000];

void initObject()
{
	gun.x = 0;
	gun.y = 0;
	pointed.x = 0;
	pointed.y = 0;
	
}

void drawBullet(float x, float y)
{
	
	glPointSize(10);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(-SCREEN_WIDTH, -SCREEN_HEIGHT,0);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glPopMatrix();
}


void update()
{
	if (shotB) {

		bullet[i].velocity = 11;

		//for (int j = 0; j <= i; j++)
		//{

			//if (!bullet[i].dead) {
		float Pang = (3.14 / 180)*(bullet[i].angle);
		bullet[i].x += bullet[i].velocity*sin(Pang) + 2;
		bullet[i].y += bullet[i].velocity*cos(Pang) + 2;
		drawBullet(bullet[i].x, bullet[i].y);
		glFlush();
		//	}
		if ((bullet[i].x > 1000 || bullet[i].y > 1000) && !bullet[i].dead) {
			bullet[i].dead = true;
			bullet[i].~position();
			shotB = true;
		}
	}
	//}

	
}

void shot()
{
	
	if ((bullet[i].x < 1000 && bullet[i].y < 1000) && i!=0 && shotB)
	{
		std::cout << "\nWait for the turn dude";
	}
	else if (shotB)
	{
		i++;
		if (PointedAngle > 45)
		{
			bullet[i].angle = PointedAngle + 5;

		}
		else
		bullet[i].angle = PointedAngle -2;
		bullet[i].velocity = 20;
		update();	
	}
	if (i >= 0)
	{
		update();
	}
	/*else if (shotB)
	{
		i++;
		bullet[i].angle = PointedAngle;
		bullet[i].velocity = 20;
		update();
	}*/
}


void drawGun()
{
	glLoadIdentity();


	for (int i = 0; i <= 360; i++)
	{
		float ang = (3.14 / 180)*i;
		float xC = gun.x + 80 * cos(ang);
		float yC = gun.y + 80 * sin(ang);

		glPushMatrix();
		glLoadIdentity();
		glTranslatef(-SCREEN_WIDTH + 20, -SCREEN_HEIGHT + 20, 0);
		glBegin(GL_LINES);
		glVertex2f(gun.x, gun.y);
		glVertex2f(xC, yC);
		glEnd();
		glPopMatrix();
	}



		glPushMatrix();
		glLoadIdentity();
		glTranslatef(-SCREEN_WIDTH , -SCREEN_HEIGHT , 0);
		if (input) {

			if (pointed.angle > 70)
				pointed.angle = 70;
			else if (pointed.angle < 30)
			{
				pointed.angle = 30;
			}
			pointed.angle += incAng;
			PointedAngle = pointed.angle;
			input = false;
		}
		glRotatef((pointed.angle*-1), 0, 0, 1);
		glBegin(GL_QUADS);
		glVertex2f(-20, 0);
		glVertex2f(20, 0);
		glVertex2f(20, 160);
		glVertex2f(-20, 160);
		glEnd();
		glPopMatrix();
}



void specialFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT: incAng = -5;
		input = true;
		break;
	case GLUT_KEY_RIGHT: incAng = 5;
		input = true;
		break;
	case GLUT_KEY_SHIFT_L: shot();
		shotB = true;
		break;
	default: incAng = 0;
		break;
	}
}

bool init ()
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glOrtho(-250, 250, -250, 250, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0, 0, 0, 1);

	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
		return false;

	return true;
}


void render()
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawGun();
	update();
	glFlush();
//	e.update(-1,bullet[i]);
	Sleep(10);
	glutPostRedisplay();
	glFlush();
	//_getch();

}

//void update();

void loop()
{
	//update();
	render();
}

void reshape(int w, int h)
{
	SCREEN_WIDTH = w;
	SCREEN_HEIGHT = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	glOrtho(-w, w, -h, h, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


int main(int argc, char ** argv)
{
	
	e.setXY(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("shot");
	
	if (!init())
		return -1;

	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutSpecialFunc(specialFunc);
	glutMainLoop();

	return 0;
}