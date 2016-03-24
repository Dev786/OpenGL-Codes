#pragma once

#include<iostream>
#include<string>
using namespace std;


void initialise(std::string *a,int n)
{
	char buffer[33];
	
	for (int i = 1; i <= n; i++)
	{
		a[i] = to_string(i);
	}

}


void checkArray(string *a,int n)
{

	for (int i = 1; i <=n; i++)
	{
		printf("%s\n", a[i].c_str());
	}

}
