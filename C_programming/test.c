#include <stdio.h>

int main(void)
{
    char a, b, c, d;

    a = 'h' - 'a';
    b = (a + 1) % 26;
    c = b + 'a';
    d = ('h' + 1) % 26;
    printf("%c, %c", c, d);

    return (0);
}