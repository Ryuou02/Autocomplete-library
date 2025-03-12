/****************************************
*
* Autocomplete library
* Developed by Ryuou02
* https://github.com/Ryuou02
* 
*****************************************/
#pragma once
#include<iostream>
#include<vector>
#include<stack>
using namespace std;
class autocomplete
{
	//string* recentlyUsedWords;	// set of recently used words
	//int* recentInsertion;		// recently inserted location in recently used words.

	int wordnum;					// number of words in string* words;
	bool isnew;						// boolean to indicate whether memory was allocated using 'new' or not	
	stack<int> begin,ends;			// beginning and end of word range 
	string buffer;	
	vector<string> wordset;
	int guess;
	void getGuess();		// retrieves the guessed word based on word in buffer.
public:
	char mostRecentChar;
	autocomplete(string* wordset,int wordsnumber);
	autocomplete(const char* wordset[], int wordsnumber);
	bool guessExists() {
		if (guess > -1)
			return true;
		else
			return false;
	}
	bool backspace() {
		if (buffer.empty())
			return 0;
		
		buffer.pop_back();	
		if (begin.size() > 1) {
			begin.pop();
		}
		return 1;
	}
	string getBuffer() {
		return buffer;
	}
	string getGuessWriteString() {
		if (guess > -1) 
			return wordset[guess].substr(buffer.size(), wordset[guess].size() - buffer.size());
		else
			return "";
	}
	// add the character to the word in buffer, guess will get updated
	void addChar(char in);	// add character filtering and input to buffer;
	void clearWordBuffer() { 
		buffer.clear(); 
		if (!buffer.empty()) {
			throw("clear not working");
		}
		while (!begin.empty()) {
			begin.pop();
		}
		guess = -1;
	}	// clear the word buffer
	void fillBuffer() {	// fill the word buffer with the guess.
		if (guess != -1) {
			buffer = wordset[guess];
			getGuess();
		}
	}
	bool addToWordset(string word);
	string _guess() {
		if (guess != -1)
			return wordset[guess];
		else
			return "";
	}
};

void wordToACbuffer(autocomplete&, const std::string&);
