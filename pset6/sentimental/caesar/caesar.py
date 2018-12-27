# Implement Caesar cipher

import sys
from cs50 import get_string

def main():
    # Check command-line argument
    if len(sys.argv) != 2:
        print("Usage: python caesar key")
        sys.exit(1)
    key = int(sys.argv[1])

    plaintext = get_string("What to cipher? ")

    enciphered = encipher_caesar(plaintext, key)

    # Print the result
    print(f"ciphertext: {enciphered}")

# Encipher text with Caesar’s algorithm
def encipher_caesar(text, key):
    enciphered = list(text)

    # Encipher every character in the text
    for i in range(len(enciphered)):

        # Only for alphabetic characters
        char = enciphered[i]
        if char.isalpha():

            # Store offset of case
            offset = 65 if char.isupper() else 97

            shift = (ord(char) - offset + key) % 26
            enciphered[i] = chr(offset + shift)
    return ''.join(enciphered)


if __name__ == "__main__":
    main()