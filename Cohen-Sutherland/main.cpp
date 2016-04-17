#include<iostream>
#include<freeglut.h>
using namespace std;

const int INSIDE = 0;
const int TOP = 8;
const int BOTTOM = 4;
const int LEFT = 1;
const int RIGHT = 2;

int xmin = 250;
int ymin = 250;
int xmax = 750;
int ymax = 750;

float x_1, y_1, x2, y2;
float mx, my, mxs, mys;
bool init()
{
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, 1000, 1000);
	glOrtho(0, 1000, 0, 1000, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		cout << "\nGL ERROR";
		return false;
	}

	return true;
}



void reshape(int w, int h)
{
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	glOrtho(0, w, 0, h, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
void drawLine(float xf, float yf, float xs, float ys)
{
	glBegin(GL_LINES);
	glVertex2f(xf, xf);
	glVertex2f(xs, ys);
	glEnd();
}

void drawWindow()
{
	glBegin(GL_LINE_LOOP);

	glVertex2f(250, 250);
	glVertex2f(750, 250);
	glVertex2f(750, 750);
	glVertex2f(250, 750);

	glEnd();
}
int getOutcode(int x, int y)
{
	int outcode = INSIDE;

	if (x > xmax)
		outcode |= RIGHT;

	else if (x < xmin)
		outcode |= LEFT;

	if (y > ymax)
		outcode |= TOP;

	else if (y < ymin)
		outcode |= BOTTOM;

	return outcode;
}


float slope(float xf, float yf, float xs, float ys)
{
	return ((ys - yf) / (xs - xf));
}


bool cohenSoutherland()
{
	bool accept = false;
	bool done = false;

	int outcode1 = getOutcode(x_1, y_1);
	int outcode2 = getOutcode(x2, y2);
	cout << outcode1 << "   " << outcode2 << endl;
	do
	{
		if (!(outcode1 | outcode2))
		{
			accept = true;
			done = true;
			cout << "inside if" << endl;
		}
		else if (outcode1 & outcode2)
		{
			done = true;

			cout << "inside else if" << endl;
		}
		else
		{

			float x0, y0;
			int outcodeOut = outcode1 ? outcode1 : outcode2;

			if (outcodeOut & TOP)
			{
				y0 = ymax;
				x0 = x_1 + (1 / slope(x_1, y_1, x2, y2))*(ymax - y_1);
			}
			else if (outcodeOut & BOTTOM)
			{

				y0 = ymin;
				x0 = x_1 + (1 / slope(x_1, y_1, x2, y2))*(ymin - y_1);
			}
			else if (outcodeOut & LEFT)
			{

				x0 = xmin;
				y0 = y_1 + slope(x_1, y_1, x2, y2)*(xmin - x_1);
			}
			else if (outcodeOut & RIGHT)
			{
				x0 = xmax;
				y0 = y_1 + slope(x_1, y_1, x2, y2)*(xmax - x_1);
			}

			if (outcodeOut == outcode1)
			{
				x_1 = x0;
				y_1 = y0;
				outcode1 = getOutcode(x_1, y_1);
			}
			else
			{
				x2 = x0;
				y2 = y0;
				outcode2 = getOutcode(x2, y2);
			}

			cout << "inside else" << endl;

		}

	} while (!done);

	if (accept)
	{
		drawLine(x_1, y_1, x2, y2);
	}


	return true;
}


void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();



	glViewport(0, 100, 500, 500);
	char *sud = "Without Algorithm";

	glRasterPos2f(300, 900);

	for (int i = 0; i < 17; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, sud[i]);
	}

	drawWindow();
	drawLine(mx, my, mxs, mys);



	glViewport(500, 100, 500, 500);

	glRasterPos2f(300, 900);
	char *su = "Cohen Sutherland";
	for (int i = 0; i < 17; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, su[i]);
	}
	drawWindow();
	cohenSoutherland();
	glutSwapBuffers();

}



int main(int argc, char *argv[])
{


	cout << "\nEnter Coordinates for Line: \n";
	cout << "\nFirst point\n";
	cin >> x_1;
	cin >> y_1;
	cout << "\nSecond point:\n";
	cin >> x2;
	cin >> y2;

	mx = x_1;
	my = y_1;
	mxs = x2;
	mys = y2;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Cohen Sutherlan");

	if (!init())
	{
		return 0;
	}

	glutDisplayFunc(render);
	//glutReshapeFunc(reshape);
	glutMainLoop();
}