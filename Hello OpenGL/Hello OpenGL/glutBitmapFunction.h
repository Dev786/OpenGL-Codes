#pragma once

#include<freeglut.h>

void printBitmap(char *string, void* Format, float x, float  y)
{
	glRasterPos2f(x, y);

	char *c = string;
	glRasterPos2f(x, y);
	while (*c != NULL)
		glutBitmapCharacter(Format, *c++);
}

