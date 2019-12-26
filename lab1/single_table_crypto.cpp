//
// Created by 佘崧林 on 2019/12/18.
//
#include <iostream>
#include <map>
#include <string>

const std::map<char, char> conv_table = {
        {'a', 'z'}, {'b', 'y'}, {'c', 'x'}, {'d', 'w'}, {'e', 'v'},
        {'f', 'u'}, {'g', 't'}, {'h', 's'}, {'i', 'r'}, {'j', 'q'},
        {'k', 'p'}, {'l', 'o'}, {'m', 'n'}, {'n', 'm'}, {'o', 'l'},
        {'p', 'k'}, {'q', 'j'}, {'r', 'i'}, {'s', 'h'}, {'t', 'g'},
        {'u', 'f'}, {'v', 'e'}, {'w', 'd'}, {'x', 'c'}, {'y', 'b'},
        {'z', 'a'},
};
const char *src = nullptr;
char *dst = nullptr;
int length;

void repl_char(int index) {
    assert(index < length);
    if (src[index] <= 'z' && src[index] >= 'a') {
        dst[index] = conv_table.at(src[index]);
    } else if (src[index] <= 'Z' && src[index] >= 'A') {
        dst[index] = char('A' + (conv_table.at('a' + (src[index] - 'A')) - 'a'));
    } else {
        dst[index] = src[index];
    }
}

void repl_all() {
    assert(src != nullptr && dst != nullptr);
    std::cout << "Plain text:" << src << std::endl;
    for (int index = 0; index < length; index++) {
        repl_char(index);
    }
    dst[length] = '\0';
    std::cout << "Cipher text:" << dst << std::endl;
}

int main () {
    std::string input;
    std::cout << "text: ";
    while( std::getline(std::cin, input) ) {
        src = input.c_str();
        length = input.length();
        delete []dst;
        dst = new char[length + 1];
        repl_all();
        std::cout << "text: ";
    }
    return 0;
}