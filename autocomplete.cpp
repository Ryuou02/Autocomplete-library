/****************************************
*
* Autocomplete library
* Developed by Ryuou02
* https://github.com/Ryuou02
*
*****************************************/

#include "autocomplete.h"
#include<chrono>
#include<algorithm>
#include<string>
#include<fstream>

void wordToACbuffer(autocomplete& obj, const std::string& sentence) {	// get the most recent word from sentence and add it to autocomplete buffer
	int cursor = sentence.size() - 1;
	while (cursor >= 0 && sentence[cursor] >= 'a' && sentence[cursor] <= 'z')
		cursor--;
	cursor++;
	while (cursor < sentence.size())
		obj.addChar(sentence[cursor++]);
}

autocomplete::autocomplete(string* wordset, int datasize) {
	wordnum = datasize;
	std::ofstream filewrite("logs.txt");
	this->wordset = vector<string>(datasize);
	for (int i = 0; i < datasize; i++) {
		this->wordset[i] = wordset[i];
		filewrite << wordset[i] << '\n';
	}
	filewrite.close();

}

autocomplete::autocomplete(const char* wordset[], int wordsnumber) 
{
	ofstream filewrite;
	filewrite.open("logs.txt");
	wordnum = wordsnumber;
	this->wordset = vector<string>(wordsnumber);

	for (int i = 0; i < wordsnumber; i++) {
		this->wordset[i] = string(wordset[i]);
		filewrite << wordset[i] << '\n';
	}
	std::sort(this->wordset.begin(), this->wordset.end());
	filewrite.close();
}

void autocomplete::addChar(char in){
	// normalisation
	if ('A' <= in && in <= 'Z')
		in += 32;
	if (in >= 'a' && in <= 'z') {
		buffer.push_back(in);
		getGuess();
	}
}

bool autocomplete::addToWordset(string word)
{
	int beg = 0, end = wordnum;
	int mid = (beg + end) / 2;
	while (end > beg) {
		if (wordset[mid] > word) {
			end = mid - 1;
		}
		else {
			beg = mid + 1;
		}
		mid = (end + beg) / 2;
	}
	
	if (wordset[mid] < word && wordset[mid + 1] > word) {
		wordset.insert(wordset.begin() + mid, word);
		return 1;
	}
	else {
		return 0;
	}
}

// getGuess function will return the guess of the word number generated for the corresponding word in buffer
// in case of no guess, guessExists variable is set to false and no guess is returned.
// else guessExists is true and guess is returned.
// in case of buffer size not changing, empty string is returned.
// in case of buffer being smaller, i.e. characters in buffer were deleted without use of backspace() function, then an exception is thrown
void autocomplete::getGuess()
{
	int b = lower_bound(wordset.begin(), wordset.end(), buffer) - wordset.begin();
	buffer[buffer.size() - 1] += 1;
	int e = upper_bound(wordset.begin(), wordset.end(), buffer) - wordset.begin();
	if (b < e)
		guess = b;
	else guess = -1;
	buffer[buffer.size() - 1] -= 1;
}
