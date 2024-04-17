#pragma once
#include<iostream>
#include<conio.h>
using namespace std;

class autocomplete
{
	string* words;
	int wordnum;
	void deleteguess(string guess);

public:
	autocomplete(string* wordset,int wordsnumber);
	autocomplete(const char* wordset, int wordsnumber);
	string input();
};

