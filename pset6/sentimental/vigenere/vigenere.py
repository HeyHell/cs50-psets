# Implement vigenere's algorithm

import sys
from cs50 import get_string

def main():
    # Check command-line arguments
    if len(sys.argv) != 2:
        print("Usage: python vigenere keyword")
        sys.exit(1)

    keyword = sys.argv[1]
    if not keyword.isalpha():
        print("The keyword must contain only alphabetic characters")
        sys.exit(2)

    plaintext = get_string("plaintext: ")

    ciphered = cipher_vigenere(plaintext, keyword)

    print(f"ciphered: {ciphered}")

# Eipher text using the Vigenere algorithm
def cipher_vigenere(text, key):
    # Get all shifts of key
    keyshifts = list(ord(x.lower()) - 97 for x in key)

    # Prepare to word
    keyword_len = len(keyshifts)
    ciphered = list(text)
    j = 0

    # cipher every character
    for i in range(len(ciphered)):
        char = ciphered[i]
        # Only for alphabetic characters
        if not char.isalpha:
            continue

        # End of keyword
        if j >= keyword_len:
            j = 0

        # Store offset of case
        offset = 65 if ciphered[i].isupper() else 97

        shift = (ord(char) - offset + keyshifts[j]) % 26
        ciphered[i] = chr(offset + shift)
        j += 1
    return ''.join(ciphered)

if __name__ == "__main__":
    main()