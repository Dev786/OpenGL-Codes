#include<iostream>
#include<string>
#include<freeglut.h>

using namespace std;


struct elemet {

	char c[20];
};

int MAX = 5;
int tot = -1;
int width = 200;
int height = 25;
elemet a[20];
int SCREEN_WIDTH = 500; //Width of the screen
int SCREEN_HEIGHT = 500; //height of the screen

bool init()
{

	glClearColor(0, 0, 0, 1); //set the backgroung to black

	glViewport(0, 0, 500, 500); //setting the viewport i.e. where the primitive should be displayed

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-250, 250, -250, 250, -100, 100); //set the orthogonal view for the view port

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLenum error = glGetError(); //Check for the error

	if (error != GL_NO_ERROR) //if error is there
	{
		return false; //returning error has been detected
	}

	return true; //returning everything is fine go on
}


void show();
void push()
{
	if (tot >= MAX)
	{
		cout << "\nThe stack is FULL\n";
	}
	else
	{
		tot++;
		printf("\nEnter the Element: ");
		cin >> a[tot].c;
		cout << endl;
		show();

	}
}


void show()
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(0, -200, 0);

	int k = 0;

	for (int i = 0; i <= tot; i++) {

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_POLYGON);
		glVertex2f(-100, k);
		glVertex2f(100, k);
		glVertex2f(100, k + 50);
		glVertex2f(-100, k + 50);
		glEnd();

		glRasterPos2f(-2, (k + 10));

		for (int j = 0; j < strlen(a[i].c); j++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, a[i].c[j]);
		}

		k += 50;




	}

	glutSwapBuffers();

	glPopMatrix();
}


void pop()
{
	if (tot <0)
	{
		cout << "\nStack is empty \n You cannot pop\n";
	}
	else
	{
		cout << "\nElement " << a[tot].c << " is removed from stack\n";
		tot--;
		show();
	}
}



void render() //display function 
{
	glClear(GL_COLOR_BUFFER_BIT); //resetting the screen

	if (tot == -1)
	{
		char *c = "1.E or e to push";
		glRasterPos2i(-50, 0);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		c = "2.R or r to pop";
		glRasterPos2i(-50, -30);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		glFlush();
		glutSwapBuffers();

	}

	else
	{
		glFlush();
		show();
	}
}



void reshape(int w, int h) //function to call when the screen is reshaped
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h); //setting the viewport i.e. where the primitive should be displayed
	glOrtho(-250, 250, -250, 250, -100, 100); //set the orthogonal view for the view port
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}



void keyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'E' | 'e': push();
		break;

	case 'r' | 'R': pop();
		render();
		break;
	}
}


int main(int argc, char*argv[])
{
	//Main function
	glutInit(&argc, argv); //initialise glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //setting the Display mode
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); //Setting the window size
	glutCreateWindow("Stack");//Setting the name of the window

	if (!init()) //check for the error
	{
		cout << "Error" << endl;
		return -1;
	}

	glutKeyboardFunc(keyBoard);
	glutDisplayFunc(render);  //register display func
	glutReshapeFunc(reshape); //register reshape func
	glutMainLoop(); //loop the main section

	return 0;
}
