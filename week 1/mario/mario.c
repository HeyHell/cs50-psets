#include <cs50.h>
#include <stdio.h>

int main(void)
{
    unsigned int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 26);

    for (int i = 1; i <= height; i++)
    {
        for (int j = i; j < height; j++)
            printf(" ");
        for (int g = 0; g < 2; g++)
        {
            for (int j = height - i; j < height; j++)
                printf("#");
            printf("  ");
        }
        printf("\n");
    }
}