//
// Created by 佘崧林 on 2019/12/18.
//

#include <iostream>
#include <string>

const char *src = nullptr;
char *dst = nullptr;
int length = 0;
int key = 0;

void shift_char(int index) {
    assert(index < length);
    if (src[index] <= 'Z' && src[index] >= 'A') {
        dst[index] = char('A' + (src[index] - 'A' + key) % 26);
    } else if (src[index] <= 'z' && src[index] >= 'a') {
        dst[index] = char('a' + (src[index] - 'a' + key) % 26);
    } else {
        dst[index] = src[index];
    }
}

void shift_all() {
    assert(src != nullptr && dst != nullptr);
    std::cout << "Plain text:" << src << std::endl;
    for (int index = 0; index < length; index++) {
        shift_char(index);
    }
    dst[length] = '\0';
    std::cout << "Cipher text:" << dst << std::endl;
}

int main() {
    std::string input;
    std::cout << "text key> ";
    while (std::cin >> input >> key) {
        src = input.c_str();
        length = input.length();
        delete []dst;
        dst = new char[length + 1];
        shift_all();
        std::cout << "text key> ";
    }
    return 0;
}