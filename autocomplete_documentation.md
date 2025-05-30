# How to use this library (autocomplete.h)

## Loading corpus
The following constructors can be used to load the set of words being used for autocomplete - 
`autocomplete()`
-- creates an autocomplete object with no words in its wordset. 

`autocomplete(string* wordset,int wordsnumber);`
-- Load all words into an array of strings and load it into an autocomplete object.

`autocomplete(const char* wordset[], int wordsnumber);`
-- Load all words into an array of const char* and load it into an autocomplete object.

example usage - 

```C++
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
}
```

In case you want to add words further into the autocomplete object, you can use - 
`bool addToWordset(string word);`
This function returns 1 on successfully adding word to the wordset and 0 in case the word is already present in the wordset.
**Another usage of this function could be to validate whether the word is already present in the wordset.**

*example usage is present in the example program.*

## Buffer
The autocomplete object has a string buffer based on which it guesses the remaining part of the word.
Normally whenever an alphabet is typed, it is supposed to be placed into the buffer and whenever there is a non-alphabet (i.e. space) being typed, the buffer should be cleared.
These are some functions used for handling the autocomplete object buffer - 

### Retrieving the buffer
The content currently present in the autocomplete object buffer can be retrieved using - 
`string getBuffer()`

### Adding characters to the buffer
Characters can be added to the buffer using the command. Note that any character can be given as input into the buffer.
However, only alphabets, after being converted to lowercase, finally are added to the buffer.
`void addChar(char in)`

### Filling the buffer with the autocompleted word
The buffer can be filled with the word that is guessed by the autocomplete system using - 
`void fillBuffer()`

### Placing last word of a sentence into buffer
A whole sentence can be given as input into the autocomplete object and only the last word in the sentence is placed into the buffer.
`void wordToACbuffer(autocomplete&, const std::string&);`
This can be used in places like a text editor where the user may not have finished typing the word in the sentence.
So when the user returns to complete the sentence, the last word can be easily placed into the buffer.


### Clearing the buffer
The contents of the buffer can be cleared using - 
`void clearWordBuffer()`

### Clearing the most recent character in the buffer / backspace
Similar to the pop_back() operation of a string, however when the a backspace is done to the buffer, the guess is also updated.
`bool backspace()`
Returns 1 on successfully performing backspace and 0 in case the buffer is already empty.



## Guess of autocomplete object
Based on the string present in the buffer of the autocomplete object, a guess is made by the autocomplete object as to what the complete word could be, based on the wordset that is loaded into the autocomplete object.

### checking whether a guess exists
To check whether the autocomplete is able to guess the rest of the word, this function can be used - 
`bool guessExists()`

### retrieving the rest of the word based on guess
To get the string that should be added to the buffer in order to complete the word - 
`string getGuessWriteString()`
This should be used when it is known that a guess exists or else there won't be any string returned by using this function.

### Retrieving guess
Suppose you want the whole guessed word, you can use - 
`string _guess()`

# Example code
Here is an example code made for use on windows terminal - 
```C++

#include"../../colorCodes.h"
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
```


# Extra Functionalities -
## checking whether a given word exists within the wordset - 
suppose you wanted to check whether a given word exists within the wordset, no need to write extra functions, you can use this - 
`bool wordExists(std::string word)`


