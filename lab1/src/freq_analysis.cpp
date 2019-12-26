//
// Created by 佘崧林 on 2019/12/18.
//

#include <iostream>
#include <vector>
#include <map>
#include <string>

const std::vector<char> alphabet_to = {'e', 't', 'o', 'i', 'a', 'n', 's', 'r', 'h', 'l', 'd', 'u', 'c',
                                       'm', 'p', 'y', 'f', 'g', 'w', 'b', 'v', 'k', 'x', 'j', 'q', 'z', };
std::map<char, char> conv_table;

const char *src = nullptr;
char *dst = nullptr;
int length = 0;

int count_char(char message) {
    assert(message >= 'a' && message <= 'z');
    char Message = char('A' + (message - 'a'));
    int counter = 0;
    for (int i = 0; i < length; i++) {
        if (src[i] == message || src[i] == Message) counter++;
    }
    return counter;
}

void revert_map() {
    std::vector<int> counter_vec;
    counter_vec.reserve(26);
    for (int alpha = 0; alpha < 26; alpha++) {
        counter_vec.push_back( count_char(char('a' + alpha)) );
    }

    for (int alpha = 0; alpha < 26; alpha++) {
        int max_pos = alpha, max_count = counter_vec.at(alpha);
        for (int i = alpha + 1; i < 26; i++) {
            if (counter_vec.at(i) > max_count) {
                max_count = counter_vec.at(i), max_pos = i;
            }
        }
        std::swap(counter_vec[alpha], counter_vec[max_pos]);
        conv_table[char('a' + max_pos)] = alphabet_to[alpha];
        std::cout << alpha << " " << char('a' + max_pos) << " " << alphabet_to[alpha] << std::endl;
    }
}

void repl_char(int index) {
    assert(index < length);
    if (src[index] <= 'z' && src[index] >= 'a') {
        dst[index] = conv_table[ src[index] ];
    } else if (src[index] <= 'Z' && src[index] >= 'A') {
        dst[index] = char('A' + (conv_table['a' + (src[index] - 'A')] - 'a'));
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
        revert_map();
        repl_all();
        std::cout << "text: ";
    }
    return 0;
}