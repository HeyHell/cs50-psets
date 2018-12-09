#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n, c, t;
    do
    {
        n = get_float("Enter dollar amount:") * 100;
    }
    while (n < 0);

    c = 0;
    // Amount of 25 cents
    t = (n / 25);
    c += t;
    n -= 25 * c;
    // Amount of 10 cents
    t = (n / 10);
    c += t;
    n -= 10 * t;
    // Amount of 5 cents
    t = (n / 5);
    c += t;
    n -= 5 * t;
    // Amount of 1 cents
    c += n;

    // Check the result
    printf("%i\n", c);
}