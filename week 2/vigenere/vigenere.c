#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool is_valid_args(int, string[]);
string encipher(string, string);
bool isalpha_string(string);

int main(int argc, string argv[])
{
    string input, enciphered;

    if (!is_valid_args(argc, argv))
    {
        printf("Invalid arguments.\n");
        return 1;
    }

    input = get_string("plaintext:");

    enciphered = encipher(input, argv[1]);

    // Print the result.
    printf("enciphered: %s\n", enciphered);
}

// Check key
bool is_valid_args(int argc, string argv[])
{
    return argc == 2 && isalpha_string(argv[1]);
}

// Check that the string contains only alphabetic symbols.
bool isalpha_string(string text)
{
    int i;

    for (i = 0; text[i] != '\0'; i++)
        if (!isalpha(text[i]))
            return false;
    return true;
}

// Encipher text with Vigenere algorithm.
string encipher(string text, string key)
{
    int i, j, shift;

    for (i = j = 0; text[i] != '\0'; i++)
    {
        // if non-alphabetic symbols
        if (!isalpha(text[i])) continue;

        if (key[j] == '\0') j = 0;
        shift = (toupper(text[i]) + toupper(key[j])) % 26;
        if (isupper(text[i]))
            text[i] = 'A' + shift;
        else
            text[i] = 'a' + shift;

        j++;
    }

    return text;
}