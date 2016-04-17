#include "MainHeader.h"

#define LEN 8192

void printv(va_list args, const char * format)
{
	char buf[LEN];
	char *ch = buf;

	vsnprintf(buf, LEN, format, args);

	while (*ch)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,*ch++);
	}
}


void print(const char* fomat, ...)
{
	var_list args;
	va_start(args, format);
}