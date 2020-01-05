//
// Created by 佘崧林 on 2020/1/5.
//

#ifndef LAB5_TESTCASE_H
#define LAB5_TESTCASE_H

const struct md5_test_case {
    const char *plaintext;
    const char *hashtext;
} testCases[] = {
    {
        "Hello World", "e59ff97941044f85df5297e1c302d260"
    },
    {
        "Hello Worl", "7df9c6e537b0683ddbcf3a443e053142"
    },
    {
        "Hello Word", "ab37c47478377042b699f03b8769cd64"
    },
    {
        "Hello Wold", "7748957eae5acebdb32645eff8837131"
    },
    {
        "Hello orld", "41032fa65a13d1c9ad73823bd87d6902"
    },
    {
        "Hell World", "074028af8a35509ca6543808137ae050"
    },
    {
        "Helo World", "4156f0a5ccf0b61e98150c7cd7da2e16"
    },
    {
        "Hllo World", "042a1cb6170cc5af186de0faf909390c"
    },
    {
        "ello World", "7a36a259583db8df4122b9ff6c5237b1"
    }
};

#endif //LAB5_TESTCASE_H
