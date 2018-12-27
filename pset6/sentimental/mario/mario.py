# Print

from cs50 import get_int

def main():
    # Get user input
    height = get_positive_integer("What's your number? ")

    # Print the pyramid
    for i in range(1, height + 1):
        # Print the padding
        print(" " * (height - i), end = "")

        # Print both the left and right size
        for j in range(2):
            print("#" * i, end = "  " if (j == 0) else "\n")


def get_positive_integer(message):
    """Get a positive integer from user"""
    while True:
        n = get_int(message)
        if (n > 0):
            return n;

if __name__ == "__main__":
    main()