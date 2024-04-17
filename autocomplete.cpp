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
	words = wordset;
	wordnum = datasize;
}

autocomplete::autocomplete(const char* wordset, int wordsnumber)
{
	words = new string[wordsnumber];
	for (int i = 0; i < wordsnumber; i++) {
		words[i] = wordset[i];
	}
}
string autocomplete::input()
{
	char in = 0;
	string input = "";
	string guess = "";

	int pos = -1;
	int beg = 0, end = wordnum;

	while (in != 13 && in != ' ') {
		in = _getch();
		if (in == 8) {
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
			continue;
		}

		if (in >= 48 && in <= 127) {
			_putch(in);
			input += in;
			pos++;
			
			for (; beg < end; beg++) {
				if (pos < words[beg].size() && (words[beg][pos] == in)) {
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
				guess = words[(beg + end) /2].substr(pos + 1, words[(beg + end) / 2].size() - pos);
				std::cout << "\033[" << 32 << ";" << 40 << ";" << 1 << "m";;
				_cputs(guess.c_str());
				for (int i = 0; i < guess.size(); i++)
					_putch(8);
				std::cout << "\033[0m";;
			}
			else {
				// word not found
				deleteguess(guess);
				std::cout << "\033[" << 37 << ";" << 40 << ";" << 2 << "m";;
				_putch(in);
				_cputs("word not found");
				std::cout << "\033[0m";;
				for (int i = 0; i < 15; i++)
					_putch(8);
				while (in != 13 && in != ' ' && in != '\t') {
					in = _getch();
					if (in == 8) {
						if (!input.empty())
							input.pop_back();
						else
							return this->input();
						_putch(8);
						_putch(32);
						_putch(8);
						continue;
					}
					_putch(in);
					input += in;
				}
				return input;
			}
		}
		if (in == '\t' && !guess.empty()) {
			
			_cputs(guess.c_str());	//no need to delete guess
			input += guess;
			pos += guess.size();
		}
		else if (in == '\t') {
			//nothing
		}

	}

	return input;
}
