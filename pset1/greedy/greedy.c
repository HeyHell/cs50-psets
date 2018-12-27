#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n, count;

    // Asks the user how much change is owed.
    do
    {
        n = get_float("Enter dollar amount:") * 100;
    }
    while (n < 0);

    // Count the minimum number of coins.
    count = n / 25;
    n %= 25;

    count += n / 10;
    n %= 10;

    count += n / 5;
    n %= 5;

    count += n;

    // Show the result.
    printf("%i\n", count);
}