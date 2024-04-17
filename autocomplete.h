#pragma once
#include<iostream>
#include<conio.h>
using namespace std;
class autocomplete
{
	string* words;		// set of words
	int wordnum;		// number of words
	void deleteguess(string guess);	// private function, to delete the guessed word that gets printed
	bool isnew;			// boolean to indicate whether memory was allocated using 'new' or not

public:
	autocomplete(string* wordset,int wordsnumber);
	autocomplete(const char* wordset[], int wordsnumber);
	~autocomplete();
	string input();		//function returns string input given from user.
};

