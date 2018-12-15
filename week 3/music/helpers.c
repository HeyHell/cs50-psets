// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <math.h>

#include "helpers.h"

#define FREQUENCY 440
#define START 4

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // Parse numbers.
    int num = fraction[0] - '0';
    int denom = fraction[2] - '0';

    return (8 / denom) * num;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int octave  = note[strlen(note) - 1] - '0';
    double freq = FREQUENCY;

    switch (note[0])
    {
        case 'C': freq /= pow(2.0, 9.0 / 12.0); break;
        case 'D': freq /= pow(2.0, 7.0 / 12.0); break;
        case 'E': freq /= pow(2.0, 5.0 / 12.0); break;
        case 'F': freq /= pow(2.0, 4.0 / 12.0); break;
        case 'G': freq /= pow(2.0, 2.0 / 12.0); break;
        case 'A': break;
        case 'B': freq *= pow(2.0, 2.0 / 12.0); break;
    }

    if (octave > START) freq *= pow(2.0, octave - START);
    else if (octave < START) freq /= pow(2.0, START - octave);

    if (strlen(note) == 3)
    {
        double power = pow(2.0, 1.0 / 12.0);
        if (note[1] == '#') freq *= power;
        else if (note[1] == 'b') freq /= power;
    }

    return freq;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    return s[0] == '\0';
}