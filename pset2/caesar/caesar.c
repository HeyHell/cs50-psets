#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

string cipher(string, int);

int main(int argc, string argv[])
{
    string text, ciphered;
    int shift;

    // Check arguments.
    if (argc != 2 || (shift = atoi(argv[1])) <= 0)
    {
        printf("Usage: ./caesar k,\nwhere k is an integer and it's greater than 0.\n");
        return 1;
    }

    // Request user string.
    text = get_string("plaintext: ");

    // Encipher the text.
    ciphered = cipher(text, shift);

    // Print the result.
    printf("%s\n", ciphered);
}

string cipher(string text, int shift)
{
    int i, c;
    char upper;

    // Chipher the text.
    for (i = 0; text[i] != '\0'; i++)
    {
        // Character must be alphabetic.
        if (!isalpha(text[i])) continue;

        upper = toupper(text[i]);
        c = (upper - 'A' + shift) % 26;
        if (upper == text[i])
            text[i] = 'A' + c;
        else
            text[i] = 'a' + c;
    }
    return text;
}