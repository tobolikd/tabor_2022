#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

enum chartypes{NONE, CHAR, NUM};

int checkparse(char *string)
{
    for (uint8_t i = 0; string[i] != '\0'; i++)
    {
        if (string[i] < '0' || string[i] > '9')
        {
            return 1;
        }
    }
    return 0;
}

char* getcode(uint8_t nums)
{
    char* code = (char *) malloc(sizeof(char) * 4);
    code[3] = '\0';
    uint8_t idx;

    for (uint8_t i = 0; i < 3; i++)
        code[i] = rand() % ('Z' - 'A' + 1) + 'A';

    switch (nums)
    {
    case 1:
        code[rand() % 3] = rand() % ('9' - '0' + 1) + '0';
        break;

    case 2:
        idx = rand() % 3;
        code[idx] = rand() % ('9' - '0' + 1) + '0';
        code[(idx + rand() % 2 + 1) % 3] = rand() % ('9' - '0' + 1) + '0';
        break;
    
    case 3:
        for (uint8_t i = 0; i < 3; i++)
            code[rand() % 3] = rand() % ('9' - '0' + 1) + '0';
        break;
    
    default:
        std::cerr << "Number of numbers in code is not in interval <1,3>";
        break;
    }

    return code;
}

int main (int argc, char **argv)
{
    std::ofstream codes;
    codes.open("generated_codes.tex", std::ios::out | std::ios::trunc | std::ios::binary);

    if (!codes.is_open())
    {
        std::cerr << "Failed to open file codes.tex";
        return 1;
    }

    if (argc != 2)
    {
        std::cerr << "Expected 1 arg exactly";
        return 1;
    }

    if (checkparse(argv[1]))
    {
        std::cerr << "Arg couldn't be parsed";
        return 1;
    }

    srand(time(NULL));

    for (int i = atoi(argv[1]); i > 0; i--)
    {
        codes << "\\pg";
        for (uint8_t j = 0; j < 6; j++)
        {
            codes << "{";

            char* code = getcode(rand() % 3 + 1);
            codes << code;
            free(code);

            codes << "}";
        }
        codes << "\n";
    }

    codes.close();

    return 0;
}