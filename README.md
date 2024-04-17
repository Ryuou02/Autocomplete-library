# Autocomplete header file
Make the text input to your console i/o based projects more easy to use with the help of autocomplete. The set of words just need to be loaded into the autocomplete object using its constructor.
Enter the set of words as an array of `string` or as an array of `const char*` and specify the number of elements/words in the array as the other parameter.

## The constructors are - 
```
autocomplete(string* wordset,int wordsnumber);
autocomplete(const char* wordset, int wordsnumber);
```

## example usage - 
with const char* array as input - 
```
#include "autocomplete.h"        // autocomplete.h includes iostream and conio.h

int main() {
    const char* words[] = {      // note that the words in this array require to be sorted
        "are",
        "good",
        "hello",
        "how",
        "I'm",
        "you"
    };
    autocomplete a1(words,std::size(words));
    string input;
    do {
        input = a1.input();
        std::cout << "\ninput is => " << input << '\n';
    } while (input != "good");
}
```

with string array as input - 
```
#include "autocomplete.h"    // autocomplete.h includes iostream and conio.h

int main() {
    string words[] = {      // note that the words in this array require to be sorted
        "are",
        "good",
        "hello",
        "how",
        "I'm",
        "you"
    };
    autocomplete a1(words,std::size(words));
    string input;
    do {
        input = a1.input();
        std::cout << "\ninput is => " << input << '\n';
    } while (input != "good");
}
```

# important usage details - 
* The function returns backspace character ('\b') in case backspace is pressed when there is no user input.
* conio.h exists only in windows as far as I know, I don't think it's there in linux. So I don't think this would work in linux.
* if *enter* or *space* is pressed, even then a string will be returned.
