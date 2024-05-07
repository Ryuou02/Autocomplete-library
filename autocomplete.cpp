#include "autocomplete.h"
#include<string>

void autocomplete::deleteguess(string guess)
{
	if (!guess.empty()) {
		for (int i = 0; i < guess.size(); i++)
			_putch(32);
		for (int i = 0; i < guess.size(); i++)
			_putch(8);
	}
}

autocomplete::autocomplete(string* wordset, int datasize) {
	isnew = false;
	words = wordset;
	wordnum = datasize;
}

autocomplete::autocomplete(const char* wordset[], int wordsnumber)
{
	isnew = true;
	words = new string[wordsnumber];
	wordnum = wordsnumber;
	for (int i = 0; i < wordsnumber; i++) {
		//std::cout << wordset[i] << '\n';
		words[i] = string(wordset[i]);
	}
}
autocomplete::~autocomplete()
{
	if(isnew)
		delete[] words;
}
string autocomplete::input()
{
	wchar_t in = 0;
	string input = "";
	string guess = "";

	int pos = -1;
	int beg = 0, end = wordnum;

	while (in != 13 && in != ' ') {
		while (!_kbhit());
		in = _getch();

		if (in >= 33 && in <= 127) {	// is not special character
			_putch(in);
			input.push_back(in);
			pos++;
			
			for (; beg < end; beg++) {
				if (pos + 1 < words[beg].size() && (words[beg][pos] == in)) {
					break;
				}
			}
			if (beg < end) {
				for (int i = beg; i < end; i++) {
					if (pos < words[i].size() && words[i][pos] != in) {
						end = i;
						break;
					}
				}
				deleteguess(guess);
				guess = words[beg].substr(pos + 1, words[beg].size() - pos);
				std::cout << "\033[2m";
				_cputs(guess.c_str());

				for (int i = 0; i < guess.size(); i++)
					_putch(8);

				std::cout << "\033[0m";;
			}
			else {
				// word not found
				deleteguess(guess);
				while (in != 13 && in != ' ') {
					in = _getch();
					if (in >= 33 && in <= 127) {
						_putch(in);
						input.push_back(in);
					}
					else {
						switch (in) {
						case 8:
							if (!input.empty())
								input.pop_back();
							else
								return this->input();
							_putch(8);
							_putch(32);
							_putch(8);
							break;
						case 224:
							_getch();
						}
					}
				}
				input.push_back(in);
				return input;
			}
		}
		else {
			switch (in) {
			case 8:	// backspace
				if (!input.empty())
					input.pop_back();
				else
					return "\b";

				if (--pos == -1) {
					beg = 0;
					end = wordnum;
				}
				deleteguess(guess);

				_putch(8);
				_putch(32);
				_putch(8);
				break;
			case '\t':
				if(!guess.empty()) {
					_cputs(guess.c_str());	//no need to delete guess
					input += guess;
					pos += guess.size();
				}
				break;
			case 224:
				// special
				if (input.empty()) {
					input.push_back(224);
					return input;
				}
				else
					_getch();
				break;
			}
		}
	}
	deleteguess(guess);
	input.push_back(in);
	return input;
}
