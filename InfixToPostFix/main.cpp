#include<iostream>
#include<process.h>
#include<conio.h>
#include<freeglut.h>

#define MAX 500

using namespace std;

char infix[200];
char postfix[200];
char stack[MAX];
int top = -1;
int len = 50;
int height = 30;
int WordLen;
int coordX = 150;
int CoordY = 0;

void push(char a)
{
	if (top >= MAX)
	{
		cout << "\nThe stack is FULL";
		_getch();
		exit(0);
	}

	stack[++top] = a;

}

int pop()
{
	if (top == -1)
	{
		cout << "\nStack is empty";
		_getch();
		exit(0);
	}
	
	return stack[top--];
}

int peek()
{
	return stack[top];
}
int prec(char a)
{
	switch (a)
	{
	case '$':return 0;
		break;
	case '+': return 1;
		break;
	case '-': return 1;
		break;
	case '*': return 2;
		break;
	case '/': return 2;
		break;
	case '%': return 2;
		break;
	default:return 10;
		break;
	}
}


//SHOW THE STACK
void displayOnGL()
{

	
	for (int i = 0; i <= top; i++)
	{
		CoordY += 60;
		glRasterPos2f(coordX,CoordY);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,stack[i]);
		glBegin(GL_LINE_LOOP);
		glVertex2f(coordX-len, CoordY-height);
		glVertex2f(coordX+len, CoordY-height);
		glVertex2f(coordX+len, CoordY +height);
		glVertex2f(coordX-len, CoordY +height);
		glEnd();
		
	}

	CoordY = 0;
}

//Display Postfix Notation
void displayPostFix()
{

	if (peek() == '$') {
		glRasterPos2f(300, 50);
		for (int i = 0; i < WordLen; i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, postfix[i]);
		}
	}
	else {
		glRasterPos2f(300, 50);
		for (int i = 0; i < strlen(postfix); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, postfix[i]);
		}
	}

}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glRasterPos2f(150, 450);
	char *c = "INFIX TO POSTFIX";
	for (int i = 0; i < strlen(c); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
	}

	displayOnGL();
	displayPostFix();
	Sleep(1000);
	glFlush();
}

void convertToPostfix(char * infix)
{
	int k=0;
	for (int i = 0; i < strlen(infix);i++)
	{
		if (isalnum(infix[i]))
		{
			postfix[k] = infix[i];
			glLoadIdentity();
			display();
			cout << postfix << endl;
			cout << stack << endl;
			k++;
		}
		else if (prec(peek())<=prec(infix[i]))
		{
			push(infix[i]);
			glLoadIdentity();
			display();
			cout << postfix << endl;
			cout << stack << endl;
		}
		else
		{
			while(prec(peek()) > prec(infix[i])) {
				postfix[k++] = pop();
				display();
			}
			glLoadIdentity();
			push(infix[i]);
			cout << postfix << endl;
			cout << stack << endl;
		}
	}

	char c;
	c = pop();
	
	while (true)
	{
		postfix[k++] = c;
		display();
		c = pop();
		if (c == '$')
		{
			push('$');
		}
	}

	display();
	
	cout << postfix<<" "<<endl;
	cout << stack << endl;
}


bool init()
{
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, 500, 500);
	glOrtho(0, 500, 0, 500, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	return true;
}


bool ope(char c)
{
	switch (c) {
	case '+': return true;
	case '-': return true;
	case '*': return true;
	case '/': return true;
	case '%': return true;
	default: return false;
	}
}

void reshape(int w, int h)
{
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	glOrtho(0, w, 0, h, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q'|'Q': 
		exit(0);
		break;
	}
}

int main(int argc, char ** argv)
{
	push('$');
	cout << "\nPress Q or q to exit from display Mode";
	cout << "\nEnter the Infix Expression: ";
	cin >> infix;	
	WordLen = strlen(infix);

	int op = 0;
	int exp = 0;

	for (int i = 0; i < WordLen; i++)
	{
		if (isalnum(infix[i]))
		{
			exp++;
		}
		else if (ope(infix[i]))
		{
			op++;
		}

	}

	if (op != exp - 1)
	{
		cout << "\nInvalid Expression";
		_getch();
		return 0;
	}

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Infix To Postfix");
	init();
	convertToPostfix(infix);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}




