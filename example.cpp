/****************************************
*
* Autocomplete library
* Developed by Ryuou02
* https://github.com/Ryuou02
*
*****************************************/

#include<iostream>
#include<Windows.h>
#include<fstream>
#include<string.h>
#include<conio.h>
#include"autocomplete.h"

using namespace std;

int main(int argc, char** argv)
{
    string useless;
    string* words = new string[370101];
    ifstream fileread;
    fileread.open("words_pos.csv.rn");
    int i = 0;
    while(!fileread.eof() && i < 370101){
        fileread >> useless;
        fileread >> words[i++];
        fileread >> useless;
    }
    char in;
    fileread.close();
    cout << "initialisation complete\n";
    autocomplete a1(words, 370101);
    

    in = 0;
    _cputs("\033[3 q");
    while (in != '\n') {
        in = _getch();
        switch (in) {
        case 8: // backaspace
            if(a1.backspace()) {
                _putch(8);
                _putch(32);
                _putch(8);
                _cputs("\033[4E\033[1M");
                _cputs(a1.getBuffer().c_str());
                _cputs("\033[4A");
                _cputs("\033[6n");
            }
            break;
        case 10:    // newline
        case 13:    // enter
        case 32:    // space
            a1.addToWordset(a1.getBuffer());            
            a1.clearWordBuffer();
            _cputs("\033[4E\033[1M\033[4A\033[1M");
            break;
            
        case 9:     // tab
            _cputs(a1.getGuessWriteString().c_str());
            a1.fillBuffer();
            break;

        default:
            a1.addChar(in);
            _putch(in);
            _cputs("\033[2m");
            _cputs(a1.getGuessWriteString().c_str());
            _cputs("\033[0m");
            for (int i = 0; i < a1.getGuessWriteString().size(); i++)
                _putch(8);
            _cputs("\033[4E\033[1M");
            _cputs(a1.getBuffer().c_str());           
            _cputs("\033[4A");
            _cputs("\033[6n");
            do {
                in = _getch();
            } while (in != 'R');
        }
    }
}
