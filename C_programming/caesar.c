#include "cs50.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool only_digits(char *string);
char rotate(char c, int k);
int main(int argc, char *argv[])
{
    // error code printed when no or more than one argument is entered
    while (argc != 2)
    {
        printf("Usage: ./caeser key");
        break;
    }
    // error message printed when argument is not a decimal digit
    if (only_digits(argv[1]) == 0)
    {
        printf("Usage: ./caeser key");
        return (1);
    }
    else
    {
        // convert argv[1] to an int
        int key = atoi(argv[1]);
        // prompt user for plaintext
        string plaintext = get_string("plaintext:  ");

        char ciphertext[50];
        printf("ciphertext: ");

        for (int i = 0; i < strlen(plaintext); i++)
        {
            ciphertext[i] = rotate(plaintext[i], key);
            printf("%c", ciphertext[i]);
        }
        printf("\n");

        return (0);
    }

}

bool only_digits(char *string)
{
    int count = 0;
    int len = strlen(string);

    for(int i = 0; i < len; i++)
    {
        if (isdigit(string[i]) != 0)
            count += 1;
        else
            continue;
    }

    if (count == len)
        return (true);
    else
        return (false);
}

char rotate(char c, int k)
{
    char a, b, d;
    if (isalpha(c) != 0)
    {
        if (isupper(c) != 0)
        {
            a = c - 'A';
            b = (a + k) % 26;
            d = b + 'A';
            return ((char)d);
        }
        else if (islower(c) != 0)
        {
            a = c - 'a';
            b = (a + k) % 26;
            d = b + 'a';
            return ((char)d);
        }
    }
    else
    {
        return ((char)c);
    }
}
